from array import array
from os import stat

from nmigen import *
from nmigen.sim.core import *

from ..riscv.bus import bus_layout
from ..kitchensink.simplatform import SimPlatform

class RAM(Elaboratable):
    def __init__(self, *, domain, init):
        self._domain = domain
        self._init = init
        self.halt = False
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)

    def elaborate(self, platform):

        m = Module()

        comb = m.d.comb

        # This starts to fail if firmware is too big... 11804 is the largest
        # sys.setrecursionlimit(10**6) fixes it
        # However simulation becomes very slow (2m49s for dhrystone)
        # so let's fake the memory for simulation (now 1m19s)

        if isinstance(platform, SimPlatform):
            iram_rp = Record([("addr", 32), ("data", 32)])
            dram_rp = Record([("addr", 32), ("data", 32)])
            dram_wp = Record([("addr", 32), ("data", 32), ("en", 4)])

            def ram_sim_process():
                while not self.halt:
                    yield Settle()
                    i_addr = yield iram_rp.addr
                    i_data = self._init[i_addr]
                    # print(f"iram  read addr: {addr:#010x}")
                    yield iram_rp.data.eq(i_data)
                    yield Settle()
                    addr = yield dram_rp.addr
                    wmask = yield dram_wp.en
                    if wmask == 0:
                        # print(f"dram  read addr: {addr:#010x}")
                        yield dram_rp.data.eq(self._init[addr])
                    else:
                        wdata = yield dram_wp.data
                        # print(f"dram write addr: {addr:#010x} wdata: {wdata:#010x} en: {en:#06b}")
                        en_to_mask = {
                            0b0001: 0x0000_00FF,
                            0b0010: 0x0000_FF00,
                            0b0100: 0x00FF_0000,
                            0b1000: 0xFF00_0000,
                            0b1111: 0xFFFF_FFFF,
                        }
                        mask = en_to_mask[wmask]
                        self._init[addr] = (self._init[addr] & ~mask) | (wdata & mask)
                        # print(f"           data: {data:#010x} -> {self._init[addr]:#010x}")
                    yield

            platform.add_sync_process(ram_sim_process, domain=self._domain)
        else:
            ram = Memory(width=32, depth=len(self._init), init=self._init)
            m.submodules.iram_rp = iram_rp = ram.read_port(domain="comb")
            m.submodules.dram_rp = dram_rp = ram.read_port(domain="comb")
            m.submodules.dram_wp = dram_wp = ram.write_port(
                domain=self._domain, granularity=8
            )

        comb += [
            self.ibus.rdy.eq(1),
            iram_rp.addr.eq(self.ibus.addr[2:28]),
            self.ibus.rdata.eq(iram_rp.data),
        ]

        comb += [
            self.dbus.rdy.eq(1),
            dram_rp.addr.eq(self.dbus.addr[2:28]),
            self.dbus.rdata.eq(dram_rp.data),
            dram_wp.addr.eq(self.dbus.addr[2:28]),
            dram_wp.en.eq(self.dbus.wmask),
            dram_wp.data.eq(self.dbus.wdata),
        ]

        return m
