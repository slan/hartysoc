from nmigen import *
from enum import Enum, unique


@unique
class AluFunc(Enum):
    ADD = 0


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
                m.d.comb += self.out.eq((self.op1 + self.op2)[:31])

        return m
