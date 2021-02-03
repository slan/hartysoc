from enum import Enum, unique

from nmigen import *


@unique
class BranchTestFunc(Enum):
    NONE = 0
    ALWAYS = 1
    NE = 2


class BranchTester(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        self.op1 = Signal(32)
        self.op2 = Signal(32)
        self.out = Signal()
        self.func = Signal(BranchTestFunc)

    def elaborate(self, platform):
        m = Module()
        sync = m.d[self._domain]

        with m.Switch(self.func):
            with m.Case(BranchTestFunc.NONE):
                sync += self.out.eq(0)
            with m.Case(BranchTestFunc.ALWAYS):
                sync += self.out.eq(1)
            with m.Case(BranchTestFunc.NE):
                sync += self.out.eq((self.op1 ^ self.op2).any())
        return m
