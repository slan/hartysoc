import os

from nmigen import *
from nmigen.back import rtlil, verilog
from nmigen.build import *
from nmigen.sim import *


class SimPlatform(Platform):
    def __init__(self, default_frequency=100):
        super().__init__()
        self.add_resources(
            [
                Resource("sync", 0, Pins("", dir="i"), Clock(default_frequency)),
                Resource("led", 0, Pins("led0", dir="o")),
                Resource("led", 1, Pins("led1", dir="o")),
                Resource("led", 2, Pins("led2", dir="o")),
                Resource("led", 3, Pins("led3", dir="o")),
            ]
        )
        self.sync_processes = {}
        self.processes = []

    # Abstract
    connectors = []
    required_tools = []
    resources = []

    # Build
    def toolchain_prepare(self, fragment, name, **kwargs):
        pass

    default_clk = "sync"

    def build(self, elaboratable, *, build_dir, **kwargs):

        sim = Simulator(elaboratable)

        os.makedirs(build_dir, exist_ok=True)
        cwd = os.getcwd()
        try:
            os.chdir(build_dir)
            with open("top.il", "w", encoding="utf-8") as f:
                f.write(rtlil.convert(elaboratable))
            with open("top.v", "w", encoding="utf-8") as f:
                f.write(verilog.convert(elaboratable))

            for name, number in self.resources:
                clock = self.lookup(name, number).clock
                if clock is not None:
                    sim.add_clock(clock.period, domain=name)

            for process in self.processes:
                sim.add_sync_process(process)

            for domain, sync_processes in self.sync_processes.items():
                for sync_process in sync_processes:
                    sim.add_sync_process(sync_process, domain=domain)

            with sim.write_vcd("top.vcd"):
                if len(self.sync_processes) > 0:
                    sim.run()
                else:
                    sim.run_until(7, run_passive=True)
        finally:
            os.chdir(cwd)

    def add_sync_process(self, process, domain):
        self.sync_processes.setdefault(domain, []).append(process)

    def add_process(self, process):
        self.processes += [process]
