from enum import Enum, unique

from nmigen import *


@unique
class BranchTestFunc(Enum):
    NONE = 0
    ALWAYS = 1
    NE = 2


class BranchTester(Elaboratable):
    def __init__(self):
        self.op1 = Signal(32)
        self.op2 = Signal(32)
        self.out = Signal()
        self.func = Signal(BranchTestFunc)

    def elaborate(self, platform):
        m = Module()
        comb = m.d.comb

        with m.Switch(self.func):
            with m.Case(BranchTestFunc.NONE):
                comb += self.out.eq(0)
            with m.Case(BranchTestFunc.ALWAYS):
                comb += self.out.eq(1)
            with m.Case(BranchTestFunc.NE):
                comb += self.out.eq((self.op1 ^ self.op2).any())
        return m
