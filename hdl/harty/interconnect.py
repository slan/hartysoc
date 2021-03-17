from nmigen import *
from nmigen.hdl.ast import Assert, Assume
from nmigen.lib.coding import Encoder

from ..riscv.bus import bus_layout


class InterConnect(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self._devices = {}

    def get_bus(self, top_bits):
        self._devices[top_bits] = bus = Record(bus_layout)
        return bus

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.encoder_ibus = encoder_ibus = Encoder(len(self._devices))
        m.submodules.encoder_dbus = encoder_dbus = Encoder(len(self._devices))

        cache_valid = Signal()
        cache_insn = Signal(32)
        cache_dbus = Record(bus_layout)
        cache_bus_id = Signal.like(encoder_dbus.o)

        buses = Array(self._devices.values())

        with m.If(cache_valid):

            bus = buses[cache_bus_id]

            comb += [
                self.ibus.rdata.eq(cache_insn),
                self.ibus.rdy.eq(1),
                #
                bus.addr.eq(cache_dbus.addr),
                bus.rmask.eq(cache_dbus.rmask),
                bus.wmask.eq(cache_dbus.wmask),
                bus.wdata.eq(cache_dbus.wdata),
            ]
            with m.If(bus.rdy):
                comb += [
                    self.dbus.rdata.eq(bus.rdata),
                    self.dbus.rdy.eq(1),
                ]
                sync += cache_valid.eq(0)

        with m.Else():

            for i, top_bits in enumerate(self._devices.keys()):
                comb += encoder_ibus.i[i].eq(self.ibus.addr[28:] == top_bits)
            ibus = buses[encoder_ibus.o]

            with m.If(~encoder_ibus.n):

                comb += [
                    ibus.addr.eq(self.ibus.addr),
                    ibus.rmask.eq(0b1111),
                ]

                with m.If(ibus.rdy):
                    comb += [
                        self.ibus.rdata.eq(ibus.rdata),
                        self.ibus.rdy.eq(1),
                    ]

                    for i, top_bits in enumerate(self._devices.keys()):
                        comb += encoder_dbus.i[i].eq(
                            (self.dbus.addr[28:] == top_bits)
                            & (self.dbus.rmask.any() | self.dbus.wmask.any())
                        )
                    dbus = buses[encoder_dbus.o]

                    with m.If(~encoder_dbus.n):

                        with m.If(encoder_ibus.o != encoder_dbus.o):
                            comb += [
                                dbus.addr.eq(self.dbus.addr),
                                dbus.rmask.eq(self.dbus.rmask),
                                dbus.wmask.eq(self.dbus.wmask),
                                dbus.wdata.eq(self.dbus.wdata),
                            ]
                            with m.If(dbus.rdy):
                                comb += [
                                    self.dbus.rdata.eq(dbus.rdata),
                                    self.dbus.rdy.eq(1),
                                ]

                        with m.Else():
                            sync += [
                                cache_valid.eq(1),
                                #
                                cache_insn.eq(self.ibus.rdata),
                                #
                                cache_dbus.addr.eq(self.dbus.addr),
                                cache_dbus.rmask.eq(self.dbus.rmask),
                                cache_dbus.wmask.eq(self.dbus.wmask),
                                cache_dbus.wdata.eq(self.dbus.wdata),
                                #
                                cache_bus_id.eq(encoder_dbus.o),
                            ]

        return m
