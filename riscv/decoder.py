from nmigen import *

from riscv.enums import *


class Decoder(Elaboratable):
    def __init__(self):
        # In
        self.insn = Signal(32)
        self.pc = Signal(32)

        # Out
        self.mcause = Signal(32)
        self.rs1_addr = Signal(5)
        self.rs2_addr = Signal(5)
        self.rd_addr = Signal(5)
        self.imm = Signal(32)
        self.mem_rmask = Signal(4)
        self.mem_wmask = Signal(4)

        self.alu_src2_type = Signal(AluSrc2)
        self.reg_src_type = Signal(RegSrc)
        self.alu_func = Signal(AluFunc)
        self.branch_target = Signal(32)
        self.branch_cond = Signal(BranchCond)

    def elaborate(self, platform):
        m = Module()
        comb = m.d.comb

        with m.Switch(self.insn):
            with m.Case("-------------------------0110111"):  # LUI
                comb += [
                    self.rs1_addr.eq(0),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(Cat(Repl(0, 12), self.insn[12:32])),
                    self.reg_src_type.eq(RegSrc.ALU),
                    self.rd_addr.eq(self.insn[7:12]),
                    self.alu_func.eq(AluFunc.ADD),
                ]
            with m.Case("-----------------000-----0010011"):  # ADDI
                comb += [
                    # src
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(Cat(self.insn[20:32], Repl(self.insn[31], 20))),
                    # dst
                    self.reg_src_type.eq(RegSrc.ALU),
                    self.rd_addr.eq(self.insn[7:12]),
                    # func
                    self.alu_func.eq(AluFunc.ADD),
                ]
            with m.Case("0-00000------------------0110011"):  # ADD SUB XOR OR AND
                insn_func = Cat(self.insn[12:15], self.insn[30])
                with m.Switch(insn_func):
                    with m.Case(AluFunc.ADD):
                        pass
                    with m.Case(AluFunc.SUB):
                        pass
                    with m.Case(AluFunc.XOR):
                        pass
                    with m.Case(AluFunc.OR):
                        pass
                    with m.Case(AluFunc.AND):
                        pass
                    with m.Default():
                        comb += [
                            self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)
                        ]
                comb += [
                    # src
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.REG),
                    self.rs2_addr.eq(self.insn[20:25]),
                    # dst
                    self.reg_src_type.eq(RegSrc.ALU),
                    self.rd_addr.eq(self.insn[7:12]),
                    # func
                    self.alu_func.eq(insn_func),
                ]
            with m.Case("-----------------010-----0000011"):  # LW
                comb += [
                    # src
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(Cat(self.insn[20:32], Repl(self.insn[31], 20))),
                    self.alu_func.eq(AluFunc.ADD),
                    # dst
                    self.reg_src_type.eq(RegSrc.MEM),
                    self.rd_addr.eq(self.insn[7:12]),
                    self.mem_rmask.eq(0b1111),
                ]
            with m.Case("-----------------010-----0100011"):  # SW
                comb += [
                    # src
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(
                        Cat(self.insn[7:12], self.insn[25:32], Repl(self.insn[31], 20))
                    ),
                    self.alu_func.eq(AluFunc.ADD),
                    # dst
                    self.rs2_addr.eq(self.insn[20:25]),
                    # mem
                    self.mem_wmask.eq(0b1111),
                ]
            with m.Case("-------------------------1101111"):  # JAL
                comb += [
                    # src
                    self.branch_target.eq(
                        self.pc
                        + Cat(
                            0,
                            self.insn[21:31],
                            self.insn[20],
                            self.insn[12:20],
                            self.insn[31],
                            Repl(self.insn[31], 19),
                        )
                    ),
                    self.branch_cond.eq(BranchCond.ALWAYS),
                    # dst
                    self.reg_src_type.eq(RegSrc.PC_INCR),
                    self.rd_addr.eq(self.insn[7:12]),
                ]
            with m.Case("-----------------001-----1100011"):  # BNE
                comb += [
                    # src
                    self.branch_target.eq(
                        self.pc
                        + Cat(
                            0,
                            self.insn[8:12],
                            self.insn[25:31],
                            self.insn[7],
                            self.insn[31],
                            Repl(self.insn[31], 19),
                        )
                    ),
                    self.branch_cond.eq(BranchCond.NE),
                    self.alu_src2_type.eq(AluSrc2.REG),
                    self.alu_func.eq(AluFunc.SUB),
                    # dst
                    # branch
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.rs2_addr.eq(self.insn[20:25]),
                ]
            with m.Default():
                comb += [
                    self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION),
                ]

        return m
