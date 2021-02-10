from enum import Enum, unique

from nmigen import *
from nmigen.hdl.rec import *

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
    MEM = 4


@unique
class MemFuncWidth(Enum):
    NONE = 0
    B = 1
    H = 2
    W = 4
    BU = 5
    HU = 6


@unique
class TrapCause(Enum):
    ILLEGAL_INSTRUCTION = 2


rvfi_layout = [
    ("valid", 1, DIR_FANOUT),
    ("order", 64, DIR_FANOUT),
    ("insn", 32, DIR_FANOUT),
    ("trap", 1, DIR_FANOUT),
    ("halt", 1, DIR_FANOUT),
    ("intr", 1, DIR_FANOUT),
    ("mode", 2, DIR_FANOUT),
    ("ixl", 2, DIR_FANOUT),
    ("rs1_addr", 5, DIR_FANOUT),
    ("rs2_addr", 5, DIR_FANOUT),
    ("rs1_rdata", 32, DIR_FANOUT),
    ("rs2_rdata", 32, DIR_FANOUT),
    ("rd_addr", 5, DIR_FANOUT),
    ("rd_wdata", 32, DIR_FANOUT),
    ("pc_rdata", 32, DIR_FANOUT),
    ("pc_wdata", 32, DIR_FANOUT),
    ("mem_addr", 32, DIR_FANOUT),
    ("mem_rmask", 4, DIR_FANOUT),
    ("mem_wmask", 4, DIR_FANOUT),
    ("mem_rdata", 32, DIR_FANOUT),
    ("mem_wdata", 32, DIR_FANOUT),
]


class Hart(Elaboratable):
    def __init__(self, domain="sync"):
        self.registers = Registers(domain)
        self.bt = BranchTester()
        self.trap = Signal()
        self._domain = domain
        self.imem_addr = Signal(32)
        self.imem_data = Signal(32)
        self.dmem_addr = Signal(32)
        self.dmem_data = Signal(32)
        self.dmem_wr_data = Signal(32)
        self.dmem_wr_en = Signal(32)
        self.rvfi = Record(rvfi_layout)

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

        clk_fb = Signal()
        pll_locked = Signal()
        clk_out = Signal()

        pc = self.pc
        pc_plus_4 = Signal.like(pc)
        instr = self.instr
        imm = Signal(12)

        # Control
        alu_src1_type = Signal(AluSrc1)
        alu_src2_type = Signal(AluSrc2)
        reg_src_type = Signal(RegSrc)
        mem_func_write = Signal()
        mem_func_width = Signal(MemFuncWidth)

        sync += self.mcycle.eq(self.mcycle + 1)

        with m.FSM(domain=self._domain) as fsm:
            with m.State("RST"):
                m.d.comb += [
                    self.imem_addr.eq(pc),
                ]
                m.next = "IF"
            with m.State("IF"):
                sync += [
                    instr.eq(self.imem_data),
                    pc_plus_4.eq(pc + 4),
                ]
                m.next = "ID"
            with m.State("ID"):
                # Set defaults
                sync += [
                    bt.func.eq(BranchTestFunc.NONE),
                    reg_src_type.eq(RegSrc.NONE),
                    mem_func_width.eq(MemFuncWidth.NONE),
                ]
                with m.Switch(instr):
                    with m.Case("-----------------000-----0010011"):  # ADDI
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
                        m.next = "EX"
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
                        m.next = "EX"
                    # with m.Case("-------------------------0000011"):  # LW
                    #     sync += [
                    #         # src
                    #         alu_src1_type.eq(AluSrc1.REG),
                    #         registers.r1_idx.eq(instr[15:20]),
                    #         alu_src2_type.eq(AluSrc2.IMM),
                    #         imm.eq(Cat(instr[7:12], instr[25:32])),
                    #         # dst
                    #         registers.r2_idx.eq(instr[20:25]),
                    #         mem_func_write.eq(0),
                    #         mem_func_width.eq(1 << instr[12:15]),
                    #     ]
                    #     m.next = "EX"
                    # with m.Case("-------------------------0100011"):  # SW
                    #     sync += [
                    #         # src
                    #         alu_src1_type.eq(AluSrc1.REG),
                    #         registers.r1_idx.eq(instr[15:20]),
                    #         alu_src2_type.eq(AluSrc2.IMM),
                    #         imm.eq(Cat(instr[7:12], instr[25:32])),
                    #         # dst
                    #         registers.r2_idx.eq(instr[20:25]),
                    #         # mem
                    #         mem_func_width.eq(1 << instr[12:15]),
                    #         mem_func_write.eq(1),
                    #     ]
                    #     m.next = "EX"
                    # with m.Case("-------------------------0000011"):  # LW
                    #     sync += [
                    #         # src
                    #         alu_src1_type.eq(AluSrc1.REG),
                    #         registers.r1_idx.eq(instr[15:20]),
                    #         alu_src2_type.eq(AluSrc2.IMM),
                    #         imm.eq(instr[20:32]),
                    #         # dst
                    #         registers.wr_idx.eq(instr[7:12]),
                    #         # mem
                    #         mem_func_width.eq(1 << instr[12:15]),
                    #         mem_func_write.eq(0),
                    #     ]
                    #     m.next = "EX"
                    # with m.Case("-------------------------1101111"):  # JAL
                    #     sync += [
                    #         # src
                    #         alu_src1_type.eq(AluSrc1.PC),
                    #         alu_src2_type.eq(AluSrc2.IMM),
                    #         imm.eq(
                    #             Cat(instr[21:31], instr[20], instr[12:20], instr[31])
                    #         ),
                    #         # dst
                    #         reg_src_type.eq(RegSrc.PC_INCR),
                    #         registers.wr_idx.eq(instr[7:12]),
                    #         # func
                    #         alu.func.eq(AluFunc.ADD),
                    #         #
                    #         bt.func.eq(BranchTestFunc.ALWAYS),
                    #     ]
                        # m.next = "EX"
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
                        m.next = "EX"
                    with m.Default():
                        sync += [
                            self.trap.eq(1),
                            self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION),
                        ]
                        m.next = "HALT"

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
                sync += [
                    self.dmem_addr.eq(alu.out),
                    self.dmem_wr_data.eq(registers.reg2),
                    self.pc.eq(Mux(bt.out, alu.out, pc_plus_4)),
                ]
                with m.Switch(mem_func_width):
                    with m.Case(MemFuncWidth.NONE):
                        sync += [
                            self.dmem_wr_en.eq(0),
                        ]
                        m.next = "WB"
                    with m.Case(MemFuncWidth.B):
                        sync += (self.dmem_wr_en.eq(0b0001),)
                        m.next = "WB"
                    with m.Case(MemFuncWidth.H):
                        sync += (self.dmem_wr_en.eq(0b0011),)
                        m.next = "WB"
                    with m.Case(MemFuncWidth.W):
                        sync += (self.dmem_wr_en.eq(0b1111),)
                        m.next = "WB"
                    with m.Default():
                        sync += [
                            self.trap.eq(1),
                            self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION),
                        ]
                        m.next = "HALT"
            with m.State("WB"):
                with m.If(registers.wr_idx.any()):
                    with m.Switch(reg_src_type):
                        with m.Case(RegSrc.ALU):
                            comb += [
                                registers.wr_en.eq(1),
                                registers.wr_data.eq(alu.out),
                            ]
                        with m.Case(RegSrc.PC_INCR):
                            comb += [
                                registers.wr_en.eq(1),
                                registers.wr_data.eq(pc_plus_4),
                            ]
                        with m.Case(RegSrc.MEM):
                            comb += [
                                registers.wr_en.eq(1),
                                registers.wr_data.eq(self.dmem_data),
                            ]

                comb += [
                    self.rvfi.valid.eq(1),
                    self.imem_addr.eq(pc),
                ]
                sync += [
                    self.minstret.eq(self.minstret + 1),
                ]
                m.next = "IF"
            with m.State("HALT"):
                pass

        comb += [
            # self.rvfi.valid.eq(),
            self.rvfi.order.eq(self.minstret),
            self.rvfi.insn.eq(instr),
            self.rvfi.trap.eq(self.trap),
            # self.rvfi.halt.eq(),
            # self.rvfi.intr.eq(),
            self.rvfi.mode.eq(Const(3)),
            self.rvfi.ixl.eq(Const(1)),
            self.rvfi.rs1_addr.eq(registers.r1_idx),
            self.rvfi.rs2_addr.eq(registers.r2_idx),
            self.rvfi.rs1_rdata.eq(registers.reg1),
            self.rvfi.rs2_rdata.eq(registers.reg2),
            self.rvfi.rd_addr.eq(registers.wr_idx),
            self.rvfi.rd_wdata.eq(registers.wr_data),
            self.rvfi.pc_rdata.eq(pc),
            self.rvfi.pc_wdata.eq(self.imem_addr),
            # self.rvfi.mem_addr.eq(),
            self.rvfi.mem_rmask.eq(0),
            self.rvfi.mem_wmask.eq(0),
            # self.rvfi.mem_rdata.eq(),
            # self.rvfi.mem_wdata.eq(),
        ]
        return m
