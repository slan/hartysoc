import os
from collections import OrderedDict

from nmigen import ClockDomain, Module
from nmigen.back import pysim, rtlil, verilog
from nmigen.back.pysim import Simulator
from nmigen.build import Clock, Platform
from nmigen.build.dsl import Attrs, Pins, Resource
from nmigen.build.run import BuildPlan


class SimPlatform(Platform):

    def __init__(self, default_frequency=20):
        super().__init__()
        self.add_resources([Resource('sync', 0, Pins('', dir='i'), Clock(default_frequency))])

    # Abstract
    connectors = []
    required_tools = []
    resources = []

    # Build
    def toolchain_prepare(self, fragment, name, **kwargs):
        pass

    default_clk = 'sync'

    def build(self, elaboratable, *, build_dir, **kwargs):

        sim = pysim.Simulator(elaboratable)

        os.makedirs(build_dir, exist_ok=True)
        cwd = os.getcwd()
        try:
            os.chdir(build_dir)
            with open('top.il', 'w', encoding='utf-8') as f:
                f.write(rtlil.convert(elaboratable))
            with open('top.v', 'w', encoding='utf-8') as f:
                f.write(verilog.convert(elaboratable))

            for name, number in self.resources:
                clock = self.lookup(name, number).clock
                if clock is not None:
                    sim.add_clock(clock.period, domain=name)

            with sim.write_vcd('top.vcd'):
                sim.run_until(5, run_passive=True)
        finally:
            os.chdir(cwd)
