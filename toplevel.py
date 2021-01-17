from typing import List
from nmigen import ClockDomain, Elaboratable, Memory, Module, Mux, Signal
from nmigen.build import Platform
from nmigen.cli import main_parser, main_runner
from nmigen.back.pysim import Simulator, ClockSignal, ResetSignal
from nmigen.asserts import Assert, Cover, Past
from nmigen_boards.arty_a7 import ArtyA7Platform
from argparse import ArgumentParser

from pll import Pll


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

        pll = Pll()
        m.domains += pll.domain
        m.submodules.pll = pll

        if platform is not None:
            m.d.comb += pll.clk_pin.eq(platform.request(platform.default_clk, dir='-'))
            for i in range(4):
                m.d.comb += platform.request('led', i).eq(core.instr[i])

        return m

    def ports(self) -> List[Signal]:
        return []


if __name__ == "__main__":

    parser = main_parser()
    args = parser.parse_args()

    top = Soc()

    if args.action is None:
        # top.d.comb += Assert(clocky.x <= 100)
        # with top.If(~Past(clocky.load)):
        #     with top.If(clocky.x == 0):
        #         pass
        #     with top.Else():
        #         top.d.sync += Assert(clocky.x == (Past(clocky.x)+1))
        ArtyA7Platform().build(top, do_program=False)

    else:

        main_runner(parser, args, top, ports=[]+top.ports())

        # def process():
        #     for i in range(20):
        #         yield

        # sim = Simulator(top)
        # sim.add_clock(1e-6)
        # sim.add_sync_process(process)
        # with sim.write_vcd('toplevel.vcd', None, traces=top.ports()):
        #     sim.run()
