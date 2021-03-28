from nmigen import *

from ..riscv.bus import bus_layout


class LEDs(Elaboratable):
    def __init__(self, *, domain):
        self._domain = domain
        self.bus = Record(bus_layout)

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        comb += self.bus.ack.eq(1)

        leds = Signal(4)

        with m.If(self.bus.wmask.any()):
            sync += leds.eq(self.bus.wdata)

        comb += [platform.request("led", i).o.eq(leds[i]) for i in range(leds.width)]

        return m
