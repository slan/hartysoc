from enum import Enum, unique

from nmigen import *

from .ram import *
from .rom import *


class ALU(Elaboratable):
    def __init__(self):
        self.op1 = Signal(32)
        self.op2 = Signal(32)
        self.out = Signal(32)
        self.func = Signal(3)

    def elaborate(self, platform):
        m = Module()

        with m.Switch(self.func):
            with m.Case(AluFunc.ADD):
                m.d.sync += self.out.eq((self.op1 + self.op2)[:32])

        return m


class Registers(Elaboratable):
    def __init__(self):
        self.wr_en = Signal()
        self.wr_data = Signal(32)
        self.wr_idx = Signal(5)
        self.r1_idx = Signal(5)
        self.r2_idx = Signal(5)
        self.reg1 = Signal(32)
        self.reg2 = Signal(32)

    def elaborate(self, platform):

        bank = Array(
            [
                Signal(32, name=f"x{i}", reset=0 if i == 0 else 0xDEADBEEF)
                for i in range(32)
            ]
        )
        self.bank = bank
        m = Module()

        m.d.comb += [
            self.reg1.eq(bank[self.r1_idx]),
            self.reg2.eq(bank[self.r2_idx]),
        ]
        with m.If(self.wr_en & self.wr_idx.any()):  # don't write to x0
            m.d.sync += bank[self.wr_idx].eq(self.wr_data)

        return m


class BranchTester(Elaboratable):
    def __init__(self):
        self.op1 = Signal(32)
        self.op2 = Signal(32)
        self.out = Signal()
        self.func = Signal(BranchTestFunc)

    def elaborate(self, platform):
        m = Module()
        with m.Switch(self.func):
            with m.Case(BranchTestFunc.NONE):
                m.d.sync += self.out.eq(0)
            with m.Case(BranchTestFunc.ALWAYS):
                m.d.sync += self.out.eq(1)
            with m.Case(BranchTestFunc.NE):
                m.d.sync += self.out.eq((self.op1 ^ self.op2).any())
        return m


@unique
class BranchTestFunc(Enum):
    NONE = 0
    ALWAYS = 1
    NE = 2


@unique
class AluFunc(Enum):
    ADD = 0


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
    def __init__(self, rom, ram):
        self.imem = rom
        self.dmem = ram

    def elaborate(self, platform):
        self.mcycle = Signal(64)
        self.minstret = Signal(64)
        self.trap = Signal()
        self.mcause = Signal(32)
        self.registers = Registers()
        self.pc = Signal(32)
        self.instr = Signal(32)

        m = Module()

        m.submodules.registers = registers = self.registers
        m.submodules.alu = alu = ALU()
        m.submodules.bt = bt = BranchTester()

        pc = self.pc
        instr = self.instr
        imm = Signal(12)
        pc_incr = Signal(32)

        # Control
        alu_src1_type = Signal(AluSrc1)
        alu_src2_type = Signal(AluSrc2)
        reg_src_type = Signal(RegSrc)
        mem_src_type = Signal(MemSrc)

        m.d.sync += self.mcycle.eq(self.mcycle + 1)
        
        with m.FSM() as fsm:
            with m.State("IF"):
                with m.If(self.imem.err):
                    m.d.comb += self.trap.eq(1),
                    m.d.sync += [
                        self.mcause.eq(TrapCause.IPAGE_FAULT)
                    ]
                    m.next = "HALT"
                with m.Else():
                    m.d.sync += [
                        instr.eq(self.imem.data),
                        pc_incr.eq(pc + 4),
                    ]
                    m.next = "ID"
            with m.State("ID"):
                m.d.sync += [
                    bt.func.eq(BranchTestFunc.NONE),
                    reg_src_type.eq(RegSrc.NONE),
                ]
                with m.Switch(instr):
                    with m.Case("-------------------------0010011"):  # ADDI
                        m.d.sync += [
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
                        m.d.sync += [
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
                        m.d.sync += []
                    with m.Case("-------------------------1101111"):  # JAL
                        m.d.sync += [
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
                        m.d.sync += [
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
                m.d.sync += [
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
                    m.d.sync += [
                        # self.dmem.wr_en.eq(1),
                        # self.dmem.addr.eq(alu.out),
                        # self.dmem.write_data.eq(registers.reg2),
                    ]
                m.next = "WB"
            with m.State("WB"):
                with m.Switch(reg_src_type):
                    with m.Case(RegSrc.ALU):
                        m.d.comb += [
                            registers.wr_en.eq(1),
                            registers.wr_data.eq(alu.out),
                        ]
                    with m.Case(RegSrc.PC_INCR):
                        m.d.comb += [
                            registers.wr_en.eq(1),
                            registers.wr_data.eq(pc_incr),
                        ]

                new_pc = Mux(bt.out, alu.out, pc_incr)
                m.d.sync += [
                    pc.eq(new_pc),
                    self.minstret.eq(self.minstret + 1),
                ]
                m.d.comb += self.imem.addr.eq(new_pc)
                m.next = "IF"
            with m.State("HALT"):
                pass

        return m
