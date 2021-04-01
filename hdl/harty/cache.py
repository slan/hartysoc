from nmigen import *

from ..riscv.bus import bus_layout


class Cache(Elaboratable):
    def __init__(self, *, domain):
        self._domain = domain
        self.bus_up = Record(bus_layout, name="icache_up")
        self.bus_down = Record(bus_layout, name="icache_down")

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        addr = Signal.like(self.bus_up.addr)
        data = Signal.like(self.bus_up.rdata)
        valid = Signal()

        with m.If(valid & (self.bus_up.addr == addr)):
            with m.If(self.bus_up.rmask.any()):
                comb += [
                    self.bus_up.rdata.eq(data),
                    self.bus_up.ack.eq(1),
                ]
        with m.Else():
            comb += self.bus_up.connect(self.bus_down)
            with m.If(self.bus_down.ack):
                sync += [
                    addr.eq(self.bus_down.addr),
                    data.eq(self.bus_down.rdata),
                    valid.eq(1),
                ]

        return m
