from nmigen import Elaboratable, Module

from core import Core
from rom import Rom
from simplatform import SimPlatform
from vga import VGA


class Soc(Elaboratable):
    rom = Rom()
    core = Core(rom.len)

    def elaborate(self, platform):
        m = Module()
        m.submodules.rom = self.rom
        m.submodules.core = self.core

        m.d.comb += self.rom.addr.eq(self.core.addr)
        m.d.comb += self.core.data.eq(self.rom.data)

        for i in range(4):
            m.d.comb += platform.request("led", i).eq(self.core.instr[i])

        if not isinstance(platform, SimPlatform):
            m.submodules.vga = VGA()

        return m

    def ports(self):
        return [self.core.ports()]
