from typing import List
from nmigen import ClockDomain, Const, Elaboratable, Memory, Module, Mux, Signal
from nmigen.build import Platform
from nmigen.cli import main_parser, main_runner
from nmigen.back.pysim import Simulator, ClockSignal, ResetSignal
from nmigen.asserts import Assert, Cover, Past
from nmigen_boards.arty_a7 import ArtyA7Platform
from argparse import ArgumentParser

from pll import Pll
from mmcm import MMCM
from nmigen.build.dsl import Attrs, Pins, Resource, Subsignal


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
            m.d.sync += self.pc.eq(Mux(self.pc ==
                                       self.data_len-1, 0, self.pc+1))
            m.d.sync += self.counter.eq(
                int(platform.default_clk_frequency if platform is not None else 4)-4)
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
            m.domains += [ClockDomain('cd1'), ClockDomain('cd2')]
        else:
            m.submodules.pll = Pll()
            cycles = int(platform.default_clk_frequency)-1
        m.submodules.b0 = Blinky(cycles, 0)
        m.submodules.b1 = Blinky(cycles, 1, 'pxl')

        return m


#    Name        1920x1080p60
#    Standard      SMPTE 274M
#    VIC                   16
#    Short Name         1080p
#    Aspect Ratio        16:9
#
#    Pixel Clock        148.5 MHz
#    TMDS Clock       1,485.0 MHz
#    Pixel Time           6.7 ns ±0.5%
#    Horizontal Freq.  67.500 kHz
#    Line Time           14.8 μs
#    Vertical Freq.    60.000 Hz
#    Frame Time          16.7 ms
#
#    Horizontal Timings
#    Active Pixels       1920
#    Front Porch           88
#    Sync Width            44
#    Back Porch           148
#    Blanking Total       280
#    Total Pixels        2200
#    Sync Polarity        pos
#
#    Vertical Timings
#    Active Lines        1080
#    Front Porch            4
#    Sync Width             5
#    Back Porch            36
#    Blanking Total        45
#    Total Lines         1125
#    Sync Polarity        pos
#
#    Active Pixels  2,073,600
#    Data Rate           3.56 Gbps
#
#    Frame Memory (Kbits)
#     8-bit Memory     16,200
#    12-bit Memory     24,300
#    24-bit Memory     48,600
#    32-bit Memory     64,800


class Screen(Elaboratable):
    def __init__(self):
        self.x = Signal(12)  # 0-2200
        self.y = Signal(11)  # 0-1125
        self.hsync = Signal()
        self.vsync = Signal()

    def elaborate(self, platform):
        m = Module()

        with m.If(self.x == 2200-1):
            m.d.pxl += self.x.eq(0)
            with m.If(self.y == 1125-1):
                m.d.pxl += self.y.eq(0)
            with m.Else():
                m.d.pxl += self.y.eq(self.y+1)
        with m.Else():
            m.d.pxl += self.x.eq(self.x+1)

        m.d.comb += self.hsync.eq((self.x >= 1920+88) & (self.x < 1920+88+44))
        m.d.comb += self.vsync.eq((self.y >= 1080+4) & (self.y < 1080+4+5))

        if platform is not None:
            r3 = platform.request("r3")
            g3 = platform.request("g3")
            b3 = platform.request("b3")

            with m.If((self.x < 1920) & (self.y < 1080)):
                with m.If(self.x < 640):
                    m.d.comb += r3.eq(0)
                    m.d.comb += g3.eq(0)
                    m.d.comb += b3.eq(1)
                with m.Elif(self.x < 640+640):
                    m.d.comb += r3.eq(1)
                    m.d.comb += g3.eq(1)
                    m.d.comb += b3.eq(1)
                with m.Else():
                    m.d.comb += r3.eq(1)
                    m.d.comb += g3.eq(0)
                    m.d.comb += b3.eq(0)

            m.d.comb += platform.request("hsync").eq(self.hsync)
            m.d.comb += platform.request("vsync").eq(self.vsync)

        return m


class VGA(Elaboratable):
    def elaborate(self, platform):
        m = Module()

        screen = Screen()

        m.submodules.pxlgen = MMCM()
        m.submodules.screen = screen

        return m


if __name__ == "__main__":

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
        
        vgaPmod = [
            Resource("hsync", 0, Pins("7", dir="o", conn=("pmod", 2)), Attrs(IOSTANDARD="LVCMOS33")),
            Resource("vsync", 0, Pins("8", dir="o", conn=("pmod", 2)), Attrs(IOSTANDARD="LVCMOS33")),
            Resource("r3", 0, Pins("4", dir="o", conn=("pmod", 1)), Attrs(IOSTANDARD="LVCMOS33")),
            Resource("g3", 0, Pins("4", dir="o", conn=("pmod", 2)), Attrs(IOSTANDARD="LVCMOS33")),
            Resource("b3", 0, Pins("10", dir="o", conn=("pmod", 1)), Attrs(IOSTANDARD="LVCMOS33")),
        ]
        platform.add_resources(vgaPmod)

        platform.build(top, do_program=False)

    else:
        main_runner(parser, args, top)
