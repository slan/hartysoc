from nmigen import *
from ..riscv.bus import bus_layout
from array import array
from os import stat


class ROM(Elaboratable):
    def __init__(self):
        with open("build/firmware.bin", mode="rb") as f:
            firmware = array("I")
            assert firmware.itemsize == 4
            file_size = stat(f.name).st_size
            assert file_size % 4 == 0
            firmware.fromfile(f, file_size // 4)
        self._mem = Memory(width=32, depth=len(firmware), init=firmware)
        self.bus = Record(bus_layout, name="rom")

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        m.submodules.rp = rp = self._mem.read_port(domain="comb")

        with m.If(self.bus.rmask.any()):
            comb += [
                rp.addr.eq(self.bus.addr[2:28]),
                self.bus.rdata.eq(rp.data),
                self.bus.rdy.eq(1),
            ]

        return m
