from nmigen import *
from nmigen.lib.coding import Encoder

from ..riscv.bus import bus_layout


class Interconnect(Elaboratable):
    def __init__(self, *, name):
        self.bus = Record(bus_layout, name=name)
        self._devices = {}

    def get_bus(self, top_bits, name):
        self._devices[top_bits] = bus = Record(bus_layout, name=name)
        return bus

    def elaborate(self, platform):
        m = Module()

        m.submodules.encoder = encoder = Encoder(width=len(self._devices))

        comb = m.d.comb

        for i, top_bits in enumerate(self._devices.keys()):
            comb += encoder.i[i].eq(
                (self.bus.addr[-4:] == top_bits)
                & (self.bus.rmask.any() | self.bus.wmask.any())
            )

        with m.If(~encoder.n):
            device_bus = Array(self._devices.values())[encoder.o]
            comb += [
                device_bus.addr[:-4].eq(self.bus.addr[:-4]),
                device_bus.rmask.eq(self.bus.rmask),
                device_bus.wmask.eq(self.bus.wmask),
                device_bus.wdata.eq(self.bus.wdata),
                self.bus.rdata.eq(device_bus.rdata),
                self.bus.ack.eq(device_bus.ack),
            ]

        return m
