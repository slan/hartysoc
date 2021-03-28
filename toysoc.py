from enum import Enum, unique
from os import WIFCONTINUED

from nmigen import *
from nmigen.hdl.rec import DIR_FANIN, DIR_FANOUT

from hdl.kitchensink import SimPlatform

bus_layout = [
    ("addr", 5, DIR_FANOUT),
    ("req", 1, DIR_FANOUT),
    ("rdata", 8, DIR_FANIN),
    ("ack", 1, DIR_FANIN),
]

device_bits = 1


class ROM(Elaboratable):
    def __init__(self, *, init, name):
        self.bus = Record(bus_layout, name=name)
        self._init = init

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        mem = Memory(
            width=self.bus.rdata.width,
            depth=2 ** (self.bus.addr.width - device_bits),
            init=self._init,
        )
        m.submodules.rp = rp = mem.read_port(domain="comb")

        with m.If(self.bus.req):
            comb += [
                rp.addr.eq(self.bus.addr),
                self.bus.rdata.eq(rp.data),
                self.bus.ack.eq(1),
            ]

        return m


class Interconnect(Elaboratable):
    def __init__(self, *, domain, bus0, bus1):
        self._domain = domain
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self.buses = [bus0, bus1]

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        cache_data = Signal.like(self.ibus.rdata)
        cache_bus_id = Signal(device_bits)

        buses = Array(self.buses)
        dbus_id = self.dbus.addr[-device_bits:]
        ibus_id = 1

        with m.FSM(domain=self._domain):
            with m.State("IBUS"):
                comb += [
                    buses[ibus_id].addr.eq(self.ibus.addr[:-device_bits]),
                    buses[ibus_id].req.eq(1),
                    self.ibus.rdata.eq(buses[ibus_id].rdata),
                    self.ibus.ack.eq(1),
                ]
                with m.If(self.dbus.req):
                    with m.If(dbus_id != ibus_id):
                        comb += [
                            buses[dbus_id].addr.eq(self.dbus.addr[:-device_bits]),
                            buses[dbus_id].req.eq(1),
                            self.dbus.rdata.eq(buses[dbus_id].rdata),
                            self.dbus.ack.eq(1),
                        ]
                    with m.Else():
                        sync += [
                            cache_data.eq(self.ibus.rdata),
                            cache_bus_id.eq(self.ibus.addr[-device_bits:]),
                        ]
                        m.next = "COLLISION"

            with m.State("COLLISION"):
                comb += [
                    self.ibus.rdata.eq(cache_data),
                    self.ibus.ack.eq(1),
                ]
                comb += [
                    buses[cache_bus_id].addr.eq(self.dbus.addr[:-device_bits]),
                    buses[cache_bus_id].req.eq(1),
                    self.dbus.rdata.eq(buses[cache_bus_id].rdata),
                    self.dbus.ack.eq(1),
                ]
                m.next = "IBUS"

        return m


class CPU(Elaboratable):
    def __init__(self, *, reset_vector, domain):
        self._reset_vector = reset_vector
        self._domain = domain
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)

    def elaborate(self, platform):

        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        pc = Signal(self.ibus.addr.width, reset=self._reset_vector)
        reg = Signal.like(self.dbus.rdata)

        comb += [
            platform.request("led", i).o.eq(reg[i]) for i in range(min(reg.width, 4))
        ]

        comb += self.ibus.addr.eq(pc)

        with m.If(self.ibus.ack):

            insn = self.ibus.rdata
            with m.Switch(insn):
                with m.Case("----0010"):
                    sync += reg[:4].eq(insn[-4:])

                with m.Case("----0011"):
                    sync += reg[-4:].eq(insn[-4:])

                with m.Case("-----100"):
                    comb += [
                        self.dbus.addr.eq(insn[-self.dbus.addr.width :]),
                        self.dbus.req.eq(1),
                    ]
                    with m.If(self.dbus.ack):
                        sync += reg.eq(self.dbus.rdata)

            with m.If(~self.dbus.req | self.dbus.ack):
                sync += pc.eq(pc + 1)

        return m


class SOC(Elaboratable):
    def elaborate(self, platform):

        domain = "sync"

        m = Module()

        comb = m.d.comb

        m.submodules.cpu = cpu = CPU(
            reset_vector=1 << (Record(bus_layout).addr.width - device_bits),
            domain=domain,
        )

        m.submodules.rom0 = rom0 = ROM(
            name="rom0",
            init=[0],
        )
        m.submodules.rom1 = rom1 = ROM(
            name="rom1",
            init=[
                0b00000000,  # NOP
                0b00000100,  # LB from ROM0   (1 cycle)
                0b10000100,  # LB from ROM1   (2 cycles)
                0b00010010,  # LILO 1
                0b00100010,  # LILO 2
                0b01000010,  # LILO 4
                0b10000010,  # LILO 8
                0b00000010,  # LILO 0
                0b00000000,  # NOP
            ],
        )

        m.submodules.interconnect = interconnect = Interconnect(
            domain=domain, bus0=rom0.bus, bus1=rom1.bus
        )

        comb += [
            cpu.ibus.connect(interconnect.ibus),
            cpu.dbus.connect(interconnect.dbus),
        ]

        if isinstance(platform, SimPlatform):

            def process():
                for _ in rom1._init:
                    yield

            platform.add_sync_process(process, domain=domain)

        return m
