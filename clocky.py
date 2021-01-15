from typing import List
from nmigen import Elaboratable, Module, Signal, Mux
from nmigen.build import Platform
from nmigen.cli import main_parser, main_runner
from nmigen.back.pysim import Simulator, ClockSignal, ResetSignal
from nmigen.asserts import Assert, Cover, Past


class Clocky(Elaboratable):
    def __init__(self):
        self.x = Signal(8)
        self.load = Signal(1)
        self.value = Signal(8)

    def elaborate(self, platform: Platform) -> Module:
        m = Module()
        with m.If(self.load):
            m.d.sync += self.x.eq(Mux(self.value < 100, self.value, 100))
        with m.Elif(self.x == 100):
            m.d.sync += self.x.eq(0)
        with m.Else():
            m.d.sync += self.x.eq(self.x + 1)

        return m

    def ports(self) -> List[Signal]:
        return [self.x, self.load, self.value]


if __name__ == "__main__":
    parser = main_parser()
    args = parser.parse_args()

    top = Module()
    clocky = Clocky()
    top.submodules.clocky = clocky

    top.d.comb += Assert(clocky.x <= 100)
    with top.If(~Past(clocky.load)):
        with top.If(clocky.x == 0):
            pass
        with top.Else():
            top.d.sync += Assert(clocky.x == (Past(clocky.x)+1))

    main_runner(parser, args, top, ports=[]+clocky.ports())
