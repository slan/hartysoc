from nmigen.sim.core import Passive, Settle
from hdl.kitchensink.simplatform import SimPlatform
from nmigen import *

from ..riscv.bus import bus_layout


class BlockROM(Elaboratable):
    def __init__(self, *, domain, init):
        self._domain = domain
        self._init = init
        self.bus = Record(bus_layout, name="brom")

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        if isinstance(platform, SimPlatform):
            rp = Record([("addr", 32), ("data", 32)])

            def brom_sim_process():
                yield Passive()
                while True:
                    rmask = yield self.bus.rmask
                    if rmask != 0:
                        addr = yield rp.addr
                        # print(
                        #     f"BROM  read addr: {addr:#010x}/{len(self._init):#010x}",
                        #     f"mask: {rmask:#06b} -> {self._init[addr]:#010x}",
                        # )
                        yield rp.data.eq(self._init[addr])
                    yield

            platform.add_sync_process(brom_sim_process, domain=self._domain)

        else:
            mem = Memory(width=32, depth=len(self._init), init=self._init)
            m.submodules.rp = rp = mem.read_port(domain=self._domain)

        comb += rp.addr.eq(self.bus.addr[2:-4])

        with m.FSM(domain=self._domain):
            with m.State("WAIT"):
                with m.If(self.bus.rmask.any()):
                    m.next = "ACK"
            with m.State("ACK"):
                comb += [
                    self.bus.rdata.eq(rp.data),
                    self.bus.ack.eq(1),
                ]
                m.next = "WAIT"

        return m
