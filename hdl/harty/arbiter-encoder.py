from nmigen import *
from nmigen.hdl.ast import Assert, Assume
from nmigen.lib.coding import Encoder

from ..riscv.bus import bus_layout


class Arbiter(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self._devices = {}

    def get_bus(self, top_bits):
        self._devices[top_bits] = bus = Record.like(self.ibus)
        return bus

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.encoder_ibus = encoder_ibus = Encoder(len(self._devices))
        m.submodules.encoder_dbus = encoder_dbus = Encoder(len(self._devices))
        buses = Array(self._devices.values())

        icache_valid = Signal()
        icache_data = Signal(32)
        icache_addr = Signal(32, reset=-1)
        dcache_addr = Signal(32)
        dcache_rmask = Signal(4)
        dcache_wmask = Signal(32)
        dcache_wdata = Signal(32)
        ecache_o = Signal.like(encoder_ibus.o)

        with m.If(icache_valid & (self.ibus.addr == icache_addr)):
            comb += [
                self.ibus.rdata.eq(icache_data),
            ]
            dbus = buses[ecache_o]
            comb += [
                dbus.addr.eq(dcache_addr),
                dbus.rmask.eq(dcache_rmask),
                dbus.wmask.eq(dcache_wmask),
                dbus.wdata.eq(dcache_wdata),
                self.dbus.rdata.eq(dbus.rdata),
                self.dbus.rdy.eq(dbus.rdy),
            ]
            sync += [
                icache_valid.eq(0),
            ]
        with m.Else():

            for i_i, top_bits_i in enumerate(self._devices.keys()):
                comb += encoder_ibus.i[i_i].eq(self.ibus.addr[28:] == top_bits_i)
            ibus = buses[encoder_ibus.o]

            comb += [
                ibus.addr.eq(self.ibus.addr),
                ibus.rmask.eq(0b1111),
                self.ibus.rdata.eq(ibus.rdata),
            ]

            for i_d, top_bits_d in enumerate(self._devices.keys()):
                comb += encoder_dbus.i[i_d].eq(
                    (self.dbus.addr[28:] == top_bits_d)
                    & (self.dbus.rmask.any() | self.dbus.wmask.any())
                )
            dbus = buses[encoder_dbus.o]

            with m.If(encoder_dbus.n | (encoder_ibus.o != encoder_dbus.o)):
                comb += [
                    dbus.addr.eq(self.dbus.addr),
                    dbus.rmask.eq(self.dbus.rmask),
                    dbus.wmask.eq(self.dbus.wmask),
                    dbus.wdata.eq(self.dbus.wdata),
                    self.dbus.rdata.eq(dbus.rdata),
                    self.dbus.rdy.eq(dbus.rdy),
                ]

            with m.Else():
                sync += [
                    icache_valid.eq(1),
                    icache_addr.eq(self.ibus.addr),
                    icache_data.eq(self.ibus.rdata),
                    #
                    dcache_addr.eq(self.dbus.addr),
                    dcache_rmask.eq(self.dbus.rmask),
                    dcache_wmask.eq(self.dbus.wmask),
                    dcache_wdata.eq(self.dbus.wdata),
                    #
                    ecache_o.eq(encoder_ibus.o),
                ]

        return m
