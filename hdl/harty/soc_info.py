from nmigen import *
from struct import *

from ..riscv.bus import bus_layout


class SOCInfo(Elaboratable):
    def __init__(self, *, version, freq):
        self._version = version
        self._freq = freq
        self.bus = Record(bus_layout, name="soc_info")

    def elaborate(self, platform):
        m = Module()

        # write freq first
        init = [round(self._freq), 0, 0, 0]

        # write greetings message
        message = (
            f"hartysoc {self._version} @{round(self._freq/1000)/1000}MHz - Bonjour\n"
        )

        # null-terminate
        message += "\0"
        # add padding
        message += "\0" * (-(len(message) % 4) % 4)
        # pack to unsigned int
        init += unpack(f"{len(message)//4}I", message.encode("ascii"))

        rom = Memory(width=32, depth=len(init), init=init)
        m.submodules.rom_rp = rom_rp = rom.read_port(domain="comb")

        with m.If(self.bus.rmask.any()):
            m.d.comb += [
                self.bus.ack.eq(1),
                rom_rp.addr.eq(self.bus.addr[2:28]),
                self.bus.rdata.eq(rom_rp.data),
            ]

        return m
