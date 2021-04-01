from nmigen import *

from ..riscv.bus import bus_layout
from .cache import Cache
from .interconnect import Interconnect


class MMU(Elaboratable):
    def __init__(self, *, domain):
        self._domain = domain
        self._device_buses = {}
        self.ibus = Record(bus_layout, name="ibus")
        self.dbus = Record(bus_layout, name="dbus")
        self.err = Signal()

    def plug(self, top_bits, dbus, both=False, ibus=None):
        self._device_buses[top_bits] = (dbus, both, ibus)

    def elaborate(self, platform):
        m = Module()

        m.submodules.icache = icache = Cache(domain=self._domain)
        m.submodules.iic = iic = Interconnect(name="iic")
        m.submodules.dic = dic = Interconnect(name="dic")

        comb = m.d.comb

        comb += [
            self.ibus.connect(icache.bus_up),
            icache.bus_down.connect(iic.bus),
            self.dbus.connect(dic.bus),
        ]

        for top_bits, (dbus, both, ibus) in self._device_buses.items():
            if ibus is not None:
                comb += [
                    iic.get_bus(top_bits, name=ibus.name).connect(ibus),
                    dic.get_bus(top_bits, name=dbus.name).connect(dbus),
                ]
            elif both:
                iic_bus = iic.get_bus(top_bits, name=dbus.name)
                with m.If(iic_bus.rmask.any()):
                    comb += iic_bus.connect(dbus)
                with m.Else():
                    comb += dic.get_bus(top_bits, name=dbus.name).connect(dbus)
            else:
                comb += dic.get_bus(top_bits, name=dbus.name).connect(dbus)


        return m
