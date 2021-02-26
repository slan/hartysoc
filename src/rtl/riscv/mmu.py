from nmigen import *
from .bus import *

class MMU(Elaboratable):
    def __init__(self):
        self.bus = Record(bus_layout)
        self._devices = []

    def add_device(self, bus, start,end):
        self._devices += [(bus, start, end)]

    def elaborate(self, platform):
        m = Module()

        for bus, start, end in self._devices:
            with m.If((self.bus.addr>=start) & (self.bus.addr<end)):
                m.d.comb += [self.bus.connect(bus)]

        return m