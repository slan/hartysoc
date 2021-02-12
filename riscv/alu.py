from nmigen import *
from enum import Enum, unique


@unique
class AluFunc(Enum):
    ADD_SUB = 0b000
    # SLL = 0b001
    # SLT = 0b010
    # SLTU = 0b011
    XOR = 0b100
    # SRL_SLA = 0b101
    OR = 0b110
    AND = 0b111


class ALU(Elaboratable):
    def __init__(self):
        self.op1 = Signal(32)
        self.op2 = Signal(32)
        self.out = Signal(32)
        self.func = Signal(AluFunc)
        self.neg = Signal()

    def elaborate(self, platform):
        m = Module()

        with m.Switch(self.func):
            with m.Case(AluFunc.ADD_SUB):
                with m.If(self.neg):
                    m.d.comb += self.out.eq(~((~self.op1 + self.op2)[:32]))
                with m.Else():
                    m.d.comb += self.out.eq((self.op1 + self.op2)[:32])
            with m.Case(AluFunc.XOR):
                m.d.comb += self.out.eq(self.op1 ^ self.op2)
            with m.Case(AluFunc.OR):
                m.d.comb += self.out.eq(self.op1 | self.op2)
            with m.Case(AluFunc.AND):
                m.d.comb += self.out.eq(self.op1 & self.op2)

        return m
