import os
from nmigen import *
from nmigen.build import *
from nmigen.sim import *
from nmigen.back import rtlil, verilog
from nmigen_boards.resources import *


class FormalPlatform(Platform):
    def __init__(self, default_frequency=100e6):
        super().__init__()
        self.add_resources(
            [
                Resource("sync", 0, Pins("clk", dir="i"), Clock(default_frequency)),
                UARTResource(0, rx="rx", tx="tx"),
            ]
        )

    # Abstract
    connectors = []
    required_tools = []
    resources = []

    # Build
    def toolchain_prepare(self, fragment, name, **kwargs):
        pass

    default_clk = "sync"

    def build(self, elaboratable, *, build_dir, **kwargs):

        print("Here")

        os.makedirs(build_dir, exist_ok=True)
        cwd = os.getcwd()
        try:
            os.chdir(build_dir)
            with open("top.il", "w", encoding="utf-8") as f:
                f.write(rtlil.convert(elaboratable))
        finally:
            os.chdir(cwd)
