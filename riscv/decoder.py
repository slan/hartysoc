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
        self.mem_wmask = Signal(4)

        self.alu_src1_type = Signal(AluSrc1)
        self.alu_src2_type = Signal(AluSrc2)
        self.reg_src_type = Signal(RegSrc)
        self.load_func = Signal(LoadFunc)
        self.alu_func = Signal(AluFunc)
        self.alu_func_ex = Signal()
        self.branch_cond = Signal(BranchCond, reset=BranchCond.NEVER)

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
                    self.alu_func.eq(AluFunc.ADD_SUB),
                ]
            with m.Case("-------------------------0010111"):  # AUIPC
                comb += [
                    self.alu_src1_type.eq(AluSrc1.PC),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(Cat(Repl(0, 12), self.insn[12:32])),
                    self.reg_src_type.eq(RegSrc.ALU),
                    self.rd_addr.eq(self.insn[7:12]),
                    self.alu_func.eq(AluFunc.ADD_SUB),
                ]
            with m.Case("-------------------------1101111"):  # JAL
                comb += [
                    self.alu_src1_type.eq(AluSrc1.PC),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(
                        Cat(
                            0,
                            self.insn[21:31],
                            self.insn[20],
                            self.insn[12:20],
                            self.insn[31],
                        ).as_signed()
                    ),
                    self.alu_func.eq(AluFunc.ADD_SUB),
                    self.branch_cond.eq(BranchCond.ALWAYS),
                    self.reg_src_type.eq(RegSrc.PC_INCR),
                    self.rd_addr.eq(self.insn[7:12]),
                ]
            with m.Case("-----------------000-----1100111"):  # JALR
                comb += [
                    self.alu_src1_type.eq(AluSrc1.REG),
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(self.insn[20:32].as_signed()),
                    self.alu_func.eq(AluFunc.ADD_SUB),
                    self.branch_cond.eq(BranchCond.ALWAYS),
                    self.reg_src_type.eq(RegSrc.PC_INCR),
                    self.rd_addr.eq(self.insn[7:12]),
                ]
            with m.Case("-------------------------1100011"):  # Bxx
                comb += [
                    # src
                    self.imm.eq(
                        Cat(
                            0,
                            self.insn[8:12],
                            self.insn[25:31],
                            self.insn[7],
                            self.insn[31],
                        ).as_signed()
                    ),
                    self.alu_src1_type.eq(AluSrc1.PC),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.alu_func.eq(AluFunc.ADD_SUB),
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.rs2_addr.eq(self.insn[20:25]),
                    self.branch_cond.eq(self.insn[12:15]),
                ]
                with m.If(self.insn[13] & ~self.insn[14]):
                    comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]
            with m.Case("-------------------------0000011"):  # Lxx
                comb += [
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(self.insn[20:32].as_signed()),
                    self.alu_func.eq(AluFunc.ADD_SUB),
                    self.load_func.eq(self.insn[12:15]),
                    self.reg_src_type.eq(RegSrc.MEM),
                    self.rd_addr.eq(self.insn[7:12]),
                ]
                with m.Switch(self.insn[12:15]):
                    with m.Case("000", "001", "010", "100", "101"):
                        pass
                    with m.Default():
                        comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]

            with m.Case("-------------------------0100011"):  # Sxx
                comb += [
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.imm.eq(Cat(self.insn[7:12], self.insn[25:32]).as_signed()),
                    self.alu_func.eq(AluFunc.ADD_SUB),
                    self.rs2_addr.eq(self.insn[20:25]),
                ]
                with m.Switch(self.insn[12:15]):
                    with m.Case("000"):
                        comb += [
                            self.mem_wmask.eq(0b0001),
                        ]
                    with m.Case("001"):
                        comb += [
                            self.mem_wmask.eq(0b0011),
                        ]
                    with m.Case("010"):
                        comb += [
                            self.mem_wmask.eq(0b1111),
                        ]
                    with m.Default():
                        comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]

            # ADDI SLTI SLTIU XORI ORI ANDI SLLI SRLI SRAI
            with m.Case("-------------------------0010011"):
                comb += [
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.IMM),
                    self.reg_src_type.eq(RegSrc.ALU),
                    self.rd_addr.eq(self.insn[7:12]),
                    self.alu_func.eq(self.insn[12:15]),
                ]
                with m.Switch(self.insn[12:15]):
                    with m.Case(
                        AluFunc.ADD_SUB,
                        AluFunc.SLT,
                        AluFunc.XOR,
                        AluFunc.OR,
                        AluFunc.AND,
                        AluFunc.SLT,
                        AluFunc.SLTU,
                    ):
                        comb += [
                            self.imm.eq(self.insn[20:32].as_signed()),
                        ]
                    with m.Case(AluFunc.SLL):
                        with m.If(self.insn[30]):
                            comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]
                        comb += [
                            self.imm.eq(self.insn[20:25]),
                        ]
                    with m.Case(AluFunc.SRL_SRA):
                        comb += [
                            self.imm.eq(self.insn[20:25]),
                            self.alu_func_ex.eq(self.insn[30]),
                        ]
                    with m.Default():
                        comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]

            # ADD SUB XOR OR AND
            with m.Case("0-00000------------------0110011"):
                comb += [
                    # src
                    self.rs1_addr.eq(self.insn[15:20]),
                    self.alu_src2_type.eq(AluSrc2.REG),
                    self.rs2_addr.eq(self.insn[20:25]),
                    # dst
                    self.reg_src_type.eq(RegSrc.ALU),
                    self.rd_addr.eq(self.insn[7:12]),
                    # func
                    self.alu_func.eq(self.insn[12:15]),
                ]
                with m.Switch(self.insn[12:15]):
                    with m.Case(AluFunc.XOR, AluFunc.OR, AluFunc.AND):
                        with m.If(self.insn[30]):
                            comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]
                    with m.Case(AluFunc.ADD_SUB):
                        comb += [
                            self.alu_func_ex.eq(self.insn[30]),
                        ]
                    with m.Default():
                        comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]
            with m.Default():
                comb += [self.mcause.eq(TrapCause.ILLEGAL_INSTRUCTION)]

        return m
