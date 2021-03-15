from nmigen import *
from nmigen.hdl.ast import Assert, Assume
from nmigen.lib.coding import Encoder

from ..riscv.bus import bus_layout


class ArbiterDual(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self._devices = {}

    def plug(self, bus, top_bits):
        self._devices[top_bits] = bus

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        icache_valid = Signal()
        icache_data = Signal(32)
        icache_addr = Signal(32, reset=-1)
        dcache_addr = Signal(32)
        dcache_rmask = Signal(4)
        dcache_wmask = Signal(32)
        dcache_wdata = Signal(32)
        is_sdram=Signal()

        sdram_bus = self._devices[3]
        console_bus = self._devices[1]
        rom_bus = self._devices[2]
        ram_bus = self._devices[7]

        with m.If(icache_valid):
            comb += [
                self.ibus.rdata.eq(icache_data),
            ]
            with m.If(is_sdram):
                comb += [
                    sdram_bus.addr.eq(dcache_addr),
                    sdram_bus.rmask.eq(dcache_rmask),
                    sdram_bus.wmask.eq(dcache_wmask),
                    sdram_bus.wdata.eq(dcache_wdata),
                    self.dbus.rdata.eq(sdram_bus.rdata),
                    self.dbus.rdy.eq(sdram_bus.rdy),
                ]
            with m.Else():
                comb += [
                    ram_bus.addr.eq(dcache_addr),
                    ram_bus.rmask.eq(dcache_rmask),
                    ram_bus.wmask.eq(dcache_wmask),
                    ram_bus.wdata.eq(dcache_wdata),
                    self.dbus.rdata.eq(ram_bus.rdata),
                    self.dbus.rdy.eq(ram_bus.rdy),
                ]
            sync += [
                icache_valid.eq(0),
            ]
        with m.Else():

            with m.Switch(self.ibus.addr[28:]):
                with m.Case(3):
                    comb += [
                        sdram_bus.addr.eq(self.ibus.addr),
                        sdram_bus.rmask.eq(0b1111),
                        self.ibus.rdata.eq(sdram_bus.rdata),
                    ]

                    with m.Switch(self.dbus.addr[28:]):
                        with m.Case(3):
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
                                is_sdram.eq(1),
                            ]
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
                        with m.Case(7):
                            comb += [
                                ram_bus.addr.eq(self.dbus.addr),
                                ram_bus.rmask.eq(self.dbus.rmask),
                                ram_bus.wmask.eq(self.dbus.wmask),
                                ram_bus.wdata.eq(self.dbus.wdata),
                                self.dbus.rdata.eq(ram_bus.rdata),
                                self.dbus.rdy.eq(ram_bus.rdy),
                            ]

                with m.Case(7):
                    comb += [
                        ram_bus.addr.eq(self.ibus.addr),
                        ram_bus.rmask.eq(0b1111),
                        self.ibus.rdata.eq(ram_bus.rdata),
                    ]

                    with m.Switch(self.dbus.addr[28:]):
                        with m.Case(3):
                            comb += [
                                sdram_bus.addr.eq(self.dbus.addr),
                                sdram_bus.rmask.eq(self.dbus.rmask),
                                sdram_bus.wmask.eq(self.dbus.wmask),
                                sdram_bus.wdata.eq(self.dbus.wdata),
                                self.dbus.rdata.eq(sdram_bus.rdata),
                                self.dbus.rdy.eq(sdram_bus.rdy),
                            ]
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
                        with m.Case(7):
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
                                is_sdram.eq(0),
                            ]

        return m
