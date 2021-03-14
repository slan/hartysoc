from nmigen import *

from .enums import *


class ALU(Elaboratable):
    def __init__(self):
        self.op1 = Signal(32)
        self.op2 = Signal(32)
        self.out = Signal(32)
        self.eq = Signal()
        self.func = Signal(AluFunc)
        self.func_ex = Signal()

    def elaborate(self, platform):
        m = Module()
        comb = m.d.comb

        comb += self.eq.eq(self.op1==self.op2)

        with m.Switch(self.func):
            with m.Case(AluFunc.ADD_SUB):
                comb += self.out.eq(
                    Mux(self.func_ex, ~((~self.op1 + self.op2)), self.op1 + self.op2)
                )
            with m.Case(AluFunc.XOR):
                comb += self.out.eq(self.op1 ^ self.op2)
            with m.Case(AluFunc.OR):
                comb += self.out.eq(self.op1 | self.op2)
            with m.Case(AluFunc.AND):
                comb += self.out.eq(self.op1 & self.op2)
            with m.Case(AluFunc.SLT):
                comb += self.out.eq(self.op1.as_signed() < self.op2.as_signed())
            with m.Case(AluFunc.SLTU):
                comb += self.out.eq(self.op1 < self.op2)
            with m.Case(AluFunc.SLL):
                comb += self.out.eq(self.op1 << self.op2[0:5])
            with m.Case(AluFunc.SRL_SRA):
                comb += self.out.eq(
                    Mux(self.func_ex, self.op1.as_signed(), self.op1) >> self.op2[0:5]
                )
        return m
