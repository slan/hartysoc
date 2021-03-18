from nmigen import *
from nmigen.hdl.rec import DIR_FANIN, DIR_FANOUT

from hdl.kitchensink import SimPlatform

bus_layout = [
    ("addr", 5, DIR_FANOUT),
    ("rmask", 1, DIR_FANOUT),
    ("wmask", 1, DIR_FANOUT),
    ("rdata", 8, DIR_FANIN),
    ("wdata", 8, DIR_FANOUT),
    ("rdy", 1, DIR_FANIN),
]


class ROM(Elaboratable):
    def __init__(self, init):
        self.bus = Record(bus_layout, name="rom_bus")
        self._init = init

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        mem = Memory(width=8, depth=8, init=self._init)
        m.submodules.rp = rp = mem.read_port(domain="comb")

        with m.If(self.bus.rmask.any()):
            comb += [
                rp.addr.eq(self.bus.addr),
                self.bus.rdata.eq(rp.data),
                self.bus.rdy.eq(1),
            ]

        return m


class RAM(Elaboratable):
    def __init__(self, init):
        self.bus = Record(bus_layout, name="ram_bus")
        self._init = init

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        mem = Memory(width=8, depth=4, init=self._init)
        m.submodules.rp = rp = mem.read_port(domain="comb")
        m.submodules.wp = wp = mem.write_port()

        with m.If(self.bus.rmask.any()):
            comb += [
                rp.addr.eq(self.bus.addr),
                self.bus.rdata.eq(rp.data),
                self.bus.rdy.eq(1),
            ]
        with m.If(self.bus.wmask.any()):
            comb += [
                wp.addr.eq(self.bus.addr),
                wp.data.eq(self.bus.wdata),
                wp.en.eq(1),
                self.bus.rdy.eq(1),
            ]

        return m


class Interconnect(Elaboratable):
    def __init__(self):
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self.devices = []

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d.sync

        cache_present = Signal()
        cache_addr = Signal.like(self.ibus.addr)
        cache_data = Signal.like(self.ibus.rdata)

        buses = Array(self.devices)
        ibus_id = self.ibus.addr[-2:]
        ibus = buses[ibus_id]
        dbus_id = self.dbus.addr[-2:]
        dbus = buses[dbus_id]
        same_device = ibus_id == dbus_id
        cache_valid = cache_present & (cache_addr == self.ibus.addr)

        with m.If(~cache_valid):
            comb += [
                ibus.rmask.eq(1),
                ibus.addr.eq(self.ibus.addr[:-2]),
                self.ibus.rdata.eq(ibus.rdata),
                self.ibus.rdy.eq(ibus.rdy),
            ]
            with m.If(ibus.rdy):
                sync += [
                    cache_addr.eq(self.ibus.addr),
                    cache_data.eq(ibus.rdata),
                    cache_present.eq(1),
                ]
        with m.Else():
            comb += [
                self.ibus.rdata.eq(cache_data),
                self.ibus.rdy.eq(1),
            ]

        with m.If(cache_valid | ~same_device):
            comb += [
                dbus.addr.eq(self.dbus.addr[:-2]),
                dbus.rmask.eq(self.dbus.rmask),
                dbus.wmask.eq(self.dbus.wmask),
                dbus.wdata.eq(self.dbus.wdata),
                self.dbus.rdata.eq(dbus.rdata),
                self.dbus.rdy.eq(dbus.rdy),
            ]

        return m


class CPU(Elaboratable):
    def __init__(self):
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self.halt = Signal(1)

    def elaborate(self, platform):

        # NOP:   00000000
        # HALT:  11111111
        # LILO:  dddd-001 load immediate to low nibble of register
        # LIHI:  dddd-011 load immediate to high nibble of register
        # LOAD:  aaaaa100 load mem address aaaaa to register
        # STORE: aaaaa110 store register to address aaaaa

        m = Module()

        comb = m.d.comb
        sync = m.d.sync

        reg = Signal(8)

        pc = Signal(5, reset=0b01000)  # boot from ROM

        comb += [platform.request("led", i).o.eq(pc[i]) for i in range(4)]

        with m.If(~self.halt):
            comb += self.ibus.addr.eq(pc)

            with m.If(self.ibus.rdy):
                insn = self.ibus.rdata
                with m.Switch(insn):
                    with m.Case("00000000"):
                        pass
                    with m.Case("11111111"):
                        sync += self.halt.eq(1)
                    with m.Case("-----001"):  # Load Immediate LOw
                        sync += reg[:4].eq(insn[4:])
                    with m.Case("-----011"):  # Load Immediate HIw
                        sync += reg[4:].eq(insn[4:])
                    with m.Case("-----100"):  # LOAD
                        comb += self.dbus.rmask.eq(1)
                    with m.Case("-----110"):  # STORE
                        comb += self.dbus.wmask.eq(1)

                mem_read = self.dbus.rmask.any()
                mem_write = self.dbus.wmask.any()
                mem_access = mem_read | mem_write

                with m.If(mem_access):
                    comb += self.dbus.addr.eq(insn[3:])
                    with m.If(mem_write):
                        comb += self.dbus.wdata.eq(reg)

                with m.If(~mem_access | self.dbus.rdy):
                    with m.If(mem_read):
                        sync += reg.eq(self.dbus.rdata)

                    sync += pc.eq(pc + 1)

        return m


class SOC(Elaboratable):
    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d.sync

        m.submodules.cpu = cpu = CPU()
        m.submodules.interconnect = interconnect = Interconnect()

        comb += [
            cpu.ibus.connect(interconnect.ibus),
            cpu.dbus.connect(interconnect.dbus),
        ]

        m.submodules.ram = ram = RAM(init=[0x12, 0x34, 0x56, 0x78])
        interconnect.devices += [ram.bus]  # device 0

        m.submodules.rom = rom = ROM(
            init=[
                0b00000000,  # NOP
                0b11010001,  # LILO M: 0100 1101
                0b01000011,  # LIHI M: 0100 1101
                0b00000110,  # STORE reg to RAM             (1 cycle)
                0b01110100,  # LOAD reg from ROM adress 6   (2 cycles)
                0b00000100,  # LOAD reg from RAM            (1 cycle)
                0b11111111,  # HALT
            ]
        )
        interconnect.devices += [rom.bus]  # device 1

        if isinstance(platform, SimPlatform):

            def process():
                while not (yield cpu.halt):
                    yield

            platform.add_sync_process(process, domain="sync")

        return m
