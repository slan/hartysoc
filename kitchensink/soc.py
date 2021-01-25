from nmigen import *

from .core import *
from .rom import *
from .simplatform import *
from .vga import *


class SOC(Elaboratable):
    def __init__(self):
        self.rom = Rom()
        self.core = Core(self.rom)

    def elaborate(self, platform):
        m = Module()
        m.submodules.rom = self.rom
        m.submodules.core = self.core

        for i in range(4):
            m.d.comb += platform.request("led", i).eq(self.core.instr[i])

        if not isinstance(platform, SimPlatform):
            m.submodules.vga = VGA()

        return m
