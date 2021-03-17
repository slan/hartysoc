from nmigen import *
from nmigen.hdl.ast import Assert, Assume
from nmigen.lib.coding import Encoder

from ..riscv.bus import bus_layout


class InterConnectSimple(Elaboratable):
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

        m.submodules.encoder_ibus = encoder_ibus = Encoder(len(self._devices))
        m.submodules.encoder_dbus = encoder_dbus = Encoder(len(self._devices))

        comb = m.d.comb
        sync = m.d[self._domain]

        cache_valid = Signal()
        cache_insn = Signal(32)
        cache_dbus = Record(bus_layout)

        ram_bus = self._devices[7]
        buses = Array([b for b in self._devices.values()])

        with m.If(cache_valid):
            comb += [
                self.ibus.rdata.eq(cache_insn),
                self.ibus.rdy.eq(1),
                #
                ram_bus.addr.eq(cache_dbus.addr),
                ram_bus.rmask.eq(cache_dbus.rmask),
                ram_bus.wmask.eq(cache_dbus.wmask),
                ram_bus.wdata.eq(cache_dbus.wdata),
                self.dbus.rdata.eq(ram_bus.rdata),
                self.dbus.rdy.eq(ram_bus.rdy),
            ]
            sync += cache_valid.eq(~self.dbus.rdy)

        with m.Else():

            for i, top_bits in enumerate(self._devices.keys()):
                comb += encoder_ibus.i[i].eq(self.ibus.addr[28:]==top_bits)

            with m.If(self.ibus.addr[28:] == 7):

                comb += [
                    ram_bus.addr.eq(self.ibus.addr),
                    ram_bus.rmask.eq(0b1111),
                ]

                with m.If(ram_bus.rdy):
                    comb += [
                        self.ibus.rdata.eq(ram_bus.rdata),
                        self.ibus.rdy.eq(1),
                    ]

                    for i, top_bits in enumerate(self._devices.keys()):
                        comb += encoder_dbus.i[i].eq(
                            (self.dbus.addr[28:] == top_bits)
                            & (self.dbus.rmask.any() | self.dbus.wmask.any())
                        )

                    with m.If(~encoder_dbus.n):
                        with m.If(
                            encoder_dbus.o == [k for k in self._devices.keys()].index(7)
                        ):  # RAM
                            sync += [
                                cache_valid.eq(1),
                                #
                                cache_insn.eq(self.ibus.rdata),
                                #
                                cache_dbus.addr.eq(self.dbus.addr),
                                cache_dbus.rmask.eq(self.dbus.rmask),
                                cache_dbus.wmask.eq(self.dbus.wmask),
                                cache_dbus.wdata.eq(self.dbus.wdata),
                            ]
                        with m.Else():
                            dbus = buses[encoder_dbus.o]
                            comb += [
                                dbus.addr.eq(self.dbus.addr),
                                dbus.rmask.eq(self.dbus.rmask),
                                dbus.wmask.eq(self.dbus.wmask),
                                dbus.wdata.eq(self.dbus.wdata),
                                self.dbus.rdata.eq(dbus.rdata),
                                self.dbus.rdy.eq(dbus.rdy),
                            ]

        return m
