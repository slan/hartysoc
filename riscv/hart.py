from enum import Enum, unique

from kitchensink import *
from nmigen import *

from .alu import *
from .branchtester import *
from .registers import *


@unique
class AluSrc1(Enum):
    NONE = 0
    REG = 1
    PC = 2


@unique
class AluSrc2(Enum):
    NONE = 0
    REG = 1
    IMM = 2


@unique
class RegSrc(Enum):
    NONE = 0
    COND = 1
    ALU = 2
    PC_INCR = 3


@unique
class MemSrc(Enum):
    NONE = 0


@unique
class TrapCause(Enum):
    IPAGE_FAULT = 12


class Hart(Elaboratable):
    def __init__(self, code, domain):
        self.imem = ROM(code, domain)
        self.dmem = RAM([], domain)
        self.registers = Registers(domain)
        self.bt = BranchTester(domain)
        self.trap = Signal()
        self._domain = domain

    def elaborate(self, platform):
        self.mcycle = Signal(64)
        self.minstret = Signal(64)
        self.mcause = Signal(32)
        self.pc = Signal(32)
        self.instr = Signal(32)

        m = Module()
        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.registers = registers = self.registers
        m.submodules.alu = alu = ALU()
        m.submodules.bt = bt = self.bt
        m.submodules.imem = self.imem
        m.submodules.dmem = self.dmem

        clk_fb = Signal()
        pll_locked = Signal()
        clk_out = Signal()

        pc = self.pc
        instr = self.instr
        imm = Signal(12)
        pc_incr = Signal(32)

        # Control
        alu_src1_type = Signal(AluSrc1)
        alu_src2_type = Signal(AluSrc2)
        reg_src_type = Signal(RegSrc)
        mem_src_type = Signal(MemSrc)

        sync += self.mcycle.eq(self.mcycle + 1)

        with m.FSM(domain=self._domain) as fsm:
            with m.State("IF"):
                    sync += [
                        instr.eq(self.imem.data),
                        pc_incr.eq(pc + 4),
                    ]
                    m.next = "ID"
            with m.State("ID"):
                sync += [
                    bt.func.eq(BranchTestFunc.NONE),
                    reg_src_type.eq(RegSrc.NONE),
                ]
                with m.Switch(instr):
                    with m.Case("-------------------------0010011"):  # ADDI
                        sync += [
                            # src
                            alu_src1_type.eq(AluSrc1.REG),
                            registers.r1_idx.eq(instr[15:20]),
                            alu_src2_type.eq(AluSrc2.IMM),
                            imm.eq(instr[20:32]),
                            # dst
                            reg_src_type.eq(RegSrc.ALU),
                            registers.wr_idx.eq(instr[7:12]),
                            # func
                            alu.func.eq(AluFunc.ADD),
                        ]
                    with m.Case("-------------------------0110011"):  # ADD
                        sync += [
                            # src
                            alu_src1_type.eq(AluSrc1.REG),
                            registers.r1_idx.eq(instr[15:20]),
                            alu_src2_type.eq(AluSrc2.REG),
                            registers.r2_idx.eq(instr[20:25]),
                            # dst
                            reg_src_type.eq(RegSrc.ALU),
                            registers.wr_idx.eq(instr[7:12]),
                            # func
                            alu.func.eq(AluFunc.ADD),
                        ]
                    with m.Case("-------------------------0100011"):  # SW
                        sync += []
                    with m.Case("-------------------------1101111"):  # JAL
                        sync += [
                            # src
                            alu_src1_type.eq(AluSrc1.PC),
                            alu_src2_type.eq(AluSrc2.IMM),
                            imm.eq(
                                Cat(instr[21:31], instr[20], instr[12:20], instr[31])
                            ),
                            # dst
                            reg_src_type.eq(RegSrc.PC_INCR),
                            registers.wr_idx.eq(instr[7:12]),
                            # func
                            alu.func.eq(AluFunc.ADD),
                            #
                            bt.func.eq(BranchTestFunc.ALWAYS),
                        ]
                    with m.Case("-------------------------1100011"):  # BNE
                        sync += [
                            # src
                            alu_src1_type.eq(AluSrc1.PC),
                            alu_src2_type.eq(AluSrc2.IMM),
                            imm.eq(
                                Cat(0, instr[8:12], instr[25:31], instr[7], instr[31])
                            ),
                            # dst
                            # branch
                            registers.r1_idx.eq(instr[15:20]),
                            registers.r2_idx.eq(instr[20:25]),
                            bt.func.eq(BranchTestFunc.NE),
                        ]
                    with m.Default():
                        pass

                m.next = "EX"
            with m.State("EX"):
                sync += [
                    alu.op1.eq(Mux(alu_src1_type == AluSrc1.PC, pc, registers.reg1)),
                    alu.op2.eq(
                        Mux(
                            alu_src2_type == AluSrc2.IMM,
                            Cat(imm, Repl(imm[11], 20)),  # sign-extend
                            registers.reg2,
                        )
                    ),
                    bt.op1.eq(registers.reg1),
                    bt.op2.eq(registers.reg2),
                ]
                m.next = "MEM"
            with m.State("MEM"):
                with m.If(mem_src_type == MemSrc.NONE):
                    sync += [
                        # self.dmem.wr_en.eq(1),
                        # self.dmem.addr.eq(alu.out),
                        # self.dmem.write_data.eq(registers.reg2),
                    ]
                m.next = "WB"
            with m.State("WB"):
                with m.Switch(reg_src_type):
                    with m.Case(RegSrc.ALU):
                        comb += [
                            registers.wr_en.eq(1),
                            registers.wr_data.eq(alu.out),
                        ]
                    with m.Case(RegSrc.PC_INCR):
                        comb += [
                            registers.wr_en.eq(1),
                            registers.wr_data.eq(pc_incr),
                        ]

                new_pc = Mux(bt.out, alu.out, pc_incr)
                sync += [
                    pc.eq(new_pc),
                    self.minstret.eq(self.minstret + 1),
                ]
                comb += self.imem.addr.eq(new_pc)
                with m.If(self.imem.err):
                    sync += [
                        self.trap.eq(1),
                        self.mcause.eq(TrapCause.IPAGE_FAULT)
                    ]
                    m.next = "HALT"
                with m.Else():
                    m.next = "IF"
            with m.State("HALT"):
                pass

        return m
