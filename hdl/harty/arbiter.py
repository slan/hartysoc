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
        self._devices[top_bits] = bus = Record(bus_layout)
        return bus

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.encoder_ibus = encoder_ibus = Encoder(len(self._devices))

        icache_retired = Signal(reset=1)
        icache_data = Signal(32)
        icache_addr = Signal(32, reset=-1)
        dbus_req = Record(bus_layout)

        console_bus = self._devices[1]
        rom_bus = self._devices[2]
        ram_bus = self._devices[7]

        with m.If(~icache_retired & (self.ibus.addr == icache_addr)):
            comb += [
                self.ibus.rdata.eq(icache_data),
                self.ibus.rdy.eq(1),
            ]

            with m.If(dbus_req.rmask.any() | dbus_req.wmask.any()):
                comb += [
                    ram_bus.addr.eq(dbus_req.addr),
                    ram_bus.rmask.eq(dbus_req.rmask),
                    ram_bus.wmask.eq(dbus_req.wmask),
                    ram_bus.wdata.eq(dbus_req.wdata),
                    self.dbus.rdata.eq(ram_bus.rdata),
                    self.dbus.rdy.eq(ram_bus.rdy),
                ]
                sync += icache_retired.eq(self.dbus.rdy)
            with m.Else():
                sync += icache_retired.eq(1)


        with m.Else():

            comb += [
                ram_bus.addr.eq(self.ibus.addr),
                ram_bus.rmask.eq(0b1111),
                self.ibus.rdata.eq(ram_bus.rdata),
                self.ibus.rdy.eq(ram_bus.rdy),
            ]

            with m.If(self.ibus.rdy):
                sync += [
                    icache_retired.eq(0),
                    icache_addr.eq(self.ibus.addr),
                    icache_data.eq(self.ibus.rdata),
                    #
                    dbus_req.addr.eq(self.dbus.addr),
                    dbus_req.rmask.eq(self.dbus.rmask),
                    dbus_req.wmask.eq(self.dbus.wmask),
                    dbus_req.wdata.eq(self.dbus.wdata),
                ]

                with m.If(self.dbus.rmask.any() | self.dbus.wmask.any()):
                    with m.Switch(self.dbus.addr[28:]):
                        with m.Case(1):
                            comb += [
                                console_bus.addr.eq(self.dbus.addr),
                                console_bus.rmask.eq(self.dbus.rmask),
                                console_bus.wmask.eq(self.dbus.wmask),
                                console_bus.wdata.eq(self.dbus.wdata),
                                self.dbus.rdata.eq(console_bus.rdata),
                                self.dbus.rdy.eq(console_bus.rdy),
                            ]
                        with m.Case(2):
                            comb += [
                                rom_bus.addr.eq(self.dbus.addr),
                                rom_bus.rmask.eq(self.dbus.rmask),
                                rom_bus.wmask.eq(self.dbus.wmask),
                                rom_bus.wdata.eq(self.dbus.wdata),
                                self.dbus.rdata.eq(rom_bus.rdata),
                                self.dbus.rdy.eq(rom_bus.rdy),
                            ]

        return m
