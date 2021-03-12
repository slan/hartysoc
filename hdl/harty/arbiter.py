from nmigen import *
from nmigen.lib.coding import Encoder

from ..riscv.bus import bus_layout


class Arbiter(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self._devices = []

    def plug(self, bus, top_bits):
        self._devices += [(bus, top_bits)]

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        # ibus - always active
        m.submodules.encoder_ibus = encoder_ibus = Encoder(len(self._devices))
        for i, (_, top_bits) in enumerate(self._devices):
            comb += [encoder_ibus.i[i].eq(self.ibus.addr[28:] == top_bits)]
        device_ibus = Array([bus for bus, _ in self._devices])[encoder_ibus.o]

        # dbus - active iff rmask!=0 or wmask!=0
        m.submodules.encoder_dbus = encoder_dbus = Encoder(len(self._devices))
        for i, (_, top_bits) in enumerate(self._devices):
            comb += [
                encoder_dbus.i[i].eq(
                    (self.dbus.addr[28:] == top_bits)
                    & (self.dbus.rmask.any() | self.dbus.wmask.any())
                )
            ]
        device_dbus = Array([bus for bus, _ in self._devices])[encoder_dbus.o]

        icache_addr = Signal(32, reset=1)
        icache_data = Signal(32)

        # Connect dbus only if there's a request and either
        # - ibus is idle (i.e. icache hit)
        # - ibus and dbus target a different device
        with m.If(~encoder_dbus.n & (encoder_ibus.o != encoder_dbus.o)):
            comb += [
                device_dbus.addr.eq(self.dbus.addr),
                device_dbus.wmask.eq(self.dbus.wmask),
                device_dbus.wdata.eq(self.dbus.wdata),
                device_dbus.rmask.eq(self.dbus.rmask),
                self.dbus.rdata.eq(device_dbus.rdata),
                self.dbus.rdy.eq(device_dbus.rdy),
            ]

        with m.If(self.ibus.addr == icache_addr):
            comb += [
                self.ibus.rdata.eq(icache_data),
                self.ibus.rdy.eq(1),
            ]
        with m.Else():
            comb += [
                device_ibus.addr.eq(self.ibus.addr),
                device_ibus.rmask.eq(0b1111),
            ]
            with m.If(device_ibus.rdy):
                sync += [
                    icache_addr.eq(self.ibus.addr),
                    icache_data.eq(device_ibus.rdata),
                ]

        return m
