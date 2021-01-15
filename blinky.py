from typing import List
from nmigen import Elaboratable, Module, Signal, Mux
from nmigen.build import Platform
from nmigen.cli import main_parser, main_runner
from nmigen.back.pysim import Simulator, ClockSignal, ResetSignal
from nmigen.asserts import Assert, Cover, Past
from nmigen_boards.arty_a7 import ArtyA7Platform


class Blinker(Elaboratable):
    def __init__(self, cycles: int):
        self.cycles = cycles
        self.counter = Signal(cycles.bit_length())
        self.out = Signal()

    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        with m.If(self.counter == 0):
            m.d.sync += [
                self.out.eq(~self.out),
                self.counter.eq(self.cycles)
            ]
        with m.Else():
            m.d.sync += self.counter.eq(self.counter-1)
        return m

    def ports(self) -> List[Signal]:
        return [self.out]


class Top(Elaboratable):
    def elaborate(self, platform):
        led = platform.request('led')
        m = Module()
        blinker = Blinker(int(platform.default_clk_frequency))
        m.submodules += blinker
        m.d.comb += led.eq(blinker.out)
        return m

if __name__ == "__main__":
    parser = main_parser()
    args = parser.parse_args()

    platform = ArtyA7Platform()
    platform.build(Top(), do_program=False)