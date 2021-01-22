from typing import List
from nmigen import ClockDomain, Const, Elaboratable, Fragment, Instance, Memory, Module, Mux, Signal
from nmigen.build import Platform, Clock
from nmigen.cli import main_parser, main_runner
from nmigen.asserts import Assert, Cover, Past
from nmigen_boards.arty_a7 import ArtyA7Platform
from argparse import ArgumentParser
from nmigen.build.dsl import Attrs, Pins, Resource, Subsignal

from vga import VGA
from pll import PLL
from simplatform import SimPlatform
from nmigen.back import pysim, rtlil, verilog
import sys
import os


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

        for i in range(4):
            m.d.comb += platform.request('led', i).eq(core.instr[i])

        if not isinstance(platform, SimPlatform):
            m.submodules.vga = VGA()

        return m


class Counter(Elaboratable):
    def __init__(self, max_value: int, domain_name: str = 'sync'):
        self._domain_name = domain_name
        self._max_value = max_value
        self._counter = Signal(range(max_value))
        self.out = Signal()

    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        domain = m.d[self._domain_name]

        with m.If(self._counter == self._max_value):
            domain += self._counter.eq(0)
            domain += self.out.eq(~self.out)
        with m.Else():
            domain += self._counter.eq(self._counter + 1)

        return m


class MultiBlinky(Elaboratable):
    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        m.submodules.pll = PLL()
        cycles = int(platform.default_clk_frequency)-1

        domain_names = ['sync', 'cd1', 'cd2', 'cd4']
        for i, domain_name in enumerate(domain_names):
            if domain_name is not None:
                counter = Counter(cycles, domain_name)
                m.submodules['counter_{}'.format(domain_name)] = counter
                m.d.comb += platform.request('led', i).eq(counter.out)

        return m


if __name__ == '__main__':

    top = MultiBlinky()

    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == 'sim':
        platform = SimPlatform()
        additional_resources = [
            Resource('led', 0, Pins('led0', dir='o')),
            Resource('led', 1, Pins('led1', dir='o')),
            Resource('led', 2, Pins('led2', dir='o')),
            Resource('led', 3, Pins('led3', dir='o')),
        ]
    elif platform_name == 'arty':
        platform = ArtyA7Platform()
        additional_resources = [Resource('vgapmod', 0,
                                         Subsignal('hsync', Pins('7', dir='o', conn=('pmod', 2)), Attrs(IOSTANDARD='LVCMOS33')),
                                         Subsignal('vsync', Pins('8', dir='o', conn=('pmod', 2)), Attrs(IOSTANDARD='LVCMOS33')),
                                         Subsignal('r', Pins('1 2 3 4', dir='o', conn=('pmod', 1)), Attrs(IOSTANDARD='LVCMOS33')),
                                         Subsignal('g', Pins('1 2 3 4', dir='o', conn=('pmod', 2)), Attrs(IOSTANDARD='LVCMOS33')),
                                         Subsignal('b', Pins('7 8 9 10', dir='o', conn=('pmod', 1)), Attrs(IOSTANDARD='LVCMOS33')),
                                         )
                                ]

    if platform is None:
        exit()

    platform.add_resources(additional_resources)
    fragment = Fragment.get(top, platform)
    platform.build(fragment, build_dir='build/{}'.format(platform_name), do_program=False)
