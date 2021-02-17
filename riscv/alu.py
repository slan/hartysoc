from nmigen import *

from riscv.enums import *


class ALU(Elaboratable):
    def __init__(self):
        self.op1 = Signal(32)
        self.op2 = Signal(32)
        self.out = Signal(32)
        self.func = Signal(AluFunc)

    def elaborate(self, platform):
        m = Module()

        with m.Switch(self.func):
            with m.Case(AluFunc.ADD):
                m.d.comb += self.out.eq((self.op1 + self.op2))
            with m.Case(AluFunc.SUB):
                m.d.comb += self.out.eq(~((~self.op1 + self.op2)))
            with m.Case(AluFunc.XOR):
                m.d.comb += self.out.eq(self.op1 ^ self.op2)
            with m.Case(AluFunc.OR):
                m.d.comb += self.out.eq(self.op1 | self.op2)
            with m.Case(AluFunc.AND):
                m.d.comb += self.out.eq(self.op1 & self.op2)
            with m.Case(AluFunc.SLT):
                m.d.comb += self.out.eq(self.op1.as_signed() < self.op2.as_signed())
            with m.Case(AluFunc.SLTU):
                m.d.comb += self.out.eq(self.op1 < self.op2)
        return m
