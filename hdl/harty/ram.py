from hdl.kitchensink.simplatform import SimPlatform
from nmigen import *
from nmigen.sim.core import Passive, Settle

from ..riscv.bus import bus_layout


class RAM(Elaboratable):
    def __init__(self, *, domain, init):
        self._domain = domain
        self._init = init
        self.ibus = Record(bus_layout, name="ibus")
        self.dbus = Record(bus_layout, name="dbus")

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        if isinstance(platform, SimPlatform):
            drp = Record([("addr", 32), ("data", 32)])
            irp = Record([("addr", 32), ("data", 32)])
            dwp = Record([("addr", 32), ("data", 32), ("en", 4)])

            def ram_sim_process():
                yield Passive()
                while True:
                    yield Settle()  
                    yield irp.data.eq(self._init[(yield irp.addr)])
                    yield Settle()  
                    rmask = yield self.dbus.rmask
                    if rmask != 0:
                        addr = yield drp.addr
                        # print(f"RAM  read addr: {addr:#010x}")
                        yield drp.data.eq(self._init[addr])
                    wmask = yield dwp.en
                    if wmask != 0:
                        addr = yield dwp.addr
                        wdata = yield dwp.data
                        en_to_mask = {
                            0b0001: 0x0000_00FF,
                            0b0010: 0x0000_FF00,
                            0b0100: 0x00FF_0000,
                            0b1000: 0xFF00_0000,
                            0b1100: 0xFFFF_0000,
                            0b0011: 0x0000_FFFF,
                            0b1111: 0xFFFF_FFFF,
                        }
                        mask = en_to_mask[wmask]
                        try:
                            # print(f"RAM write addr: {addr:#010x}")
                            self._init[addr] = (self._init[addr] & ~mask) | (
                                wdata & mask
                            )
                        except:
                            print(
                                f"RAM write addr: {addr:#010x} wdata: {wdata:#010x} wmask: {wmask:#06b}"
                            )
                            raise

                    yield

            platform.add_sync_process(ram_sim_process, domain=self._domain)

        else:
            mem = Memory(width=32, depth=len(self._init), init=self._init)
            m.submodules.irp = irp = mem.read_port(domain="comb")
            m.submodules.drp = drp = mem.read_port(domain="comb")
            m.submodules.dwp = dwp = mem.write_port(domain=self._domain, granularity=8)

        with m.If(self.ibus.rmask.any()):
            comb += [
                irp.addr.eq(self.ibus.addr[2:28]),
                self.ibus.rdata.eq(irp.data),
                self.ibus.ack.eq(1)
            ]

        with m.If(self.dbus.wmask.any()):
            comb += [
                dwp.addr.eq(self.dbus.addr[2:28]),
                dwp.en.eq(self.dbus.wmask),
                dwp.data.eq(self.dbus.wdata),
                self.dbus.ack.eq(1),
            ]
        with m.Elif(self.dbus.rmask.any()):
            comb += [
                drp.addr.eq(self.dbus.addr[2:28]),
                self.dbus.rdata.eq(drp.data),
                self.dbus.ack.eq(1),
            ]

        return m
