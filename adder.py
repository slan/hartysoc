from typing import List
from nmigen import Elaboratable, Module, Signal
from nmigen.build import Platform
from nmigen.cli import main_parser, main_runner
from nmigen.back.pysim import Simulator, ClockSignal, ResetSignal
from nmigen.asserts import Assert, Cover


class Adder(Elaboratable):
    def __init__(self):
        self.x = Signal(8)
        self.y = Signal(8)
        self.out = Signal(8)

    def elaborate(self, platform: Platform) -> Module:
        m = Module()
        m.d.comb += self.out.eq(self.x + self.y)
        return m

    def ports(self) -> List[Signal]:
        return [self.x, self.y, self.out]


if __name__ == "__main__":
    parser = main_parser()
    args = parser.parse_args()

    top = Module()
    adder = Adder()
    top.submodules.adder = adder

    top.d.comb += Assert(adder.out == (adder.x+adder.y)[:8])
    top.d.comb += Cover(adder.out == 0xAA)

    main_runner(parser, args, top, ports=[]+adder.ports())
