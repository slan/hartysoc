from typing import List
from nmigen import ClockDomain, Const, Elaboratable, Instance, Memory, Module, Mux, Signal
from nmigen.build import Platform
from nmigen.cli import main_parser, main_runner
from nmigen.back.pysim import Simulator, ClockSignal, ResetSignal
from nmigen.asserts import Assert, Cover, Past
from nmigen_boards.arty_a7 import ArtyA7Platform
from argparse import ArgumentParser
from nmigen.build.dsl import Attrs, Pins, Resource, Subsignal

from vga import VGA
from pll import PLL


class Core(Elaboratable):
    def __init__(self, data_len):
        self.pc = Signal(32)
        self.instr = Signal(32)
        self.stage = Signal(2)
        self.addr = Signal(32)
        self.data = Signal(32)
        self.data_len = data_len
        self.counter = Signal(25)

    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        with m.If(self.stage == 0):
            m.d.sync += self.addr.eq(self.pc)
            m.d.sync += self.stage.eq(1)
        with m.If(self.stage == 1):
            m.d.sync += self.instr.eq(self.data)
            m.d.sync += self.stage.eq(2)
        with m.If(self.stage == 2):
            m.d.sync += self.pc.eq(Mux(self.pc == self.data_len-1, 0, self.pc+1))
            m.d.sync += self.counter.eq(int(platform.default_clk_frequency-1) if platform is not None else 0)
            m.d.sync += self.stage.eq(3)
        with m.If(self.stage == 3):
            with m.If(self.counter == 0):
                m.d.sync += self.stage.eq(0)
            with m.Else():
                m.d.sync += self.counter.eq(self.counter-1)

        return m

    def ports(self) -> List[Signal]:
        return [self.pc, self.instr]


class Rom(Elaboratable):
    def __init__(self):
        init = [
            0b1000,
            0b0100,
            0b0010,
            0b0001,
            0b0010,
            0b0100,
        ]
        self._mem = Memory(width=32, depth=1024, init=init)
        self.data = Signal(32)
        self.addr = Signal(32)
        self.len = len(init)

    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        m.submodules.rp = rp = self._mem.read_port()
        m.d.comb += self.data.eq(rp.data)
        m.d.comb += rp.addr.eq(self.addr)

        return m


class Soc(Elaboratable):
    def elaborate(self, platform: Platform) -> Module:
        m = Module()
        rom = rom = Rom()
        core = core = Core(rom.len)
        m.submodules.rom = rom
        m.submodules.core = core

        m.d.comb += rom.addr.eq(core.addr)
        m.d.comb += core.data.eq(rom.data)

        if platform is not None:
            for i in range(4):
                m.d.comb += platform.request('led', i).eq(core.instr[i])

        return m


class Blinky(Elaboratable):
    def __init__(self, reset_value: int, id, domain_name='sync'):
        self.reset_value = reset_value
        self.counter = Signal(32, reset=reset_value)
        self.led = Signal()
        self.id = id
        self.domain_name = domain_name

    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        domain = m.d[self.domain_name]

        with m.If(self.counter == 0):
            domain += self.counter.eq(self.reset_value)
            domain += self.led.eq(~self.led)
        with m.Else():
            domain += self.counter.eq(self.counter - 1)

        if platform is not None:
            m.d.comb += platform.request('led', self.id).eq(self.led)

        return m


class MultiBlinky(Elaboratable):
    def elaborate(self, platform):
        m = Module()
        if platform is None:
            cycles = 9
            m.domains += [ClockDomain('sync'), ClockDomain('cd0'), ClockDomain('cd1')]
        else:
            m.submodules.pll = PLL()
            cycles = int(platform.default_clk_frequency)-1

        m.submodules.b0 = Blinky(cycles, 0, 'cd0')
        m.submodules.b1 = Blinky(cycles, 1, 'cd1')

        return m


if __name__ == '__main__':

    parser = main_parser()
    args = parser.parse_args()

    top = VGA()

    if args.action is None:
        # top.d.comb += Assert(clocky.x <= 100)
        # with top.If(~Past(clocky.load)):
        #     with top.If(clocky.x == 0):
        #         pass
        #     with top.Else():
        #         top.d.sync += Assert(clocky.x == (Past(clocky.x)+1))
        platform = ArtyA7Platform()

        vgaPmod = [Resource('vgapmod', 0,
                            Subsignal('hsync', Pins('7', dir='o', conn=('pmod', 2)), Attrs(IOSTANDARD='LVCMOS33')),
                            Subsignal('vsync', Pins('8', dir='o', conn=('pmod', 2)), Attrs(IOSTANDARD='LVCMOS33')),
                            Subsignal('r', Pins('1 2 3 4', dir='o', conn=('pmod', 1)), Attrs(IOSTANDARD='LVCMOS33')),
                            Subsignal('g', Pins('1 2 3 4', dir='o', conn=('pmod', 2)), Attrs(IOSTANDARD='LVCMOS33')),
                            Subsignal('b', Pins('7 8 9 10', dir='o', conn=('pmod', 1)), Attrs(IOSTANDARD='LVCMOS33')),
                            )
                   ]
        platform.add_resources(vgaPmod)

        platform.build(top, do_program=False)

    else:
        main_runner(parser, args, top)
