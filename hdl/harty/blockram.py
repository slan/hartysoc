from nmigen.sim.core import Passive, Settle
from hdl.kitchensink.simplatform import SimPlatform
from nmigen import *

from ..riscv.bus import bus_layout


class BlockRAM(Elaboratable):
    def __init__(self, *, domain, size):
        self._domain = domain
        assert size % 4 == 0
        self._init = [0] * (size // 4)
        self.bus = Record(bus_layout, name="bram")

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        if isinstance(platform, SimPlatform):
            rp = Record([("addr", 32), ("data", 32)])
            wp = Record([("addr", 32), ("data", 32), ("en", 4)])

            def bram_sim_process():
                yield Passive()
                while True:
                    rmask = yield self.bus.rmask
                    if rmask != 0:
                        addr = yield rp.addr
                        # print(f"BRAM  read addr: {addr:#010x} mask: {rmask:#06b} -> {self._init[addr]:#010x}")
                        yield rp.data.eq(self._init[addr])
                    wmask = yield wp.en
                    if wmask != 0:
                        addr = yield wp.addr
                        wdata = yield wp.data
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
                            # print(f"BRAM write addr: {addr:#010x}")
                            self._init[addr] = (self._init[addr] & ~mask) | (
                                wdata & mask
                            )
                        except:
                            print(
                                f"BRAM write addr: {addr:#010x} wdata: {wdata:#010x} wmask: {wmask:#06b}"
                            )
                            raise

                    yield

            platform.add_sync_process(bram_sim_process, domain=self._domain)

        else:
            mem = Memory(width=32, depth=len(self._init))
            m.submodules.rp = rp = mem.read_port(domain=self._domain)
            m.submodules.wp = wp = mem.write_port(domain=self._domain)

        with m.FSM(domain=self._domain):
            with m.State("WAIT"):
                with m.If(self.bus.rmask.any()):
                    comb += [
                        rp.addr.eq(self.bus.addr[2:-4]),
                    ]
                    m.next = "READ"
                with m.Elif(self.bus.wmask.any()):
                    comb += [
                        wp.addr.eq(self.bus.addr[2:-4]),
                        wp.en.eq(self.bus.wmask),
                        wp.data.eq(self.bus.wdata),
                    ]
                    m.next = "WRITE"
            with m.State("READ"):
                comb += [
                    self.bus.rdata.eq(rp.data),
                    self.bus.ack.eq(1),
                ]
                m.next = "WAIT"
            with m.State("WRITE"):
                comb += [
                    self.bus.ack.eq(1),
                ]
                m.next = "WAIT"

        return m
