from nmigen import *


class RAM(Elaboratable):
    def __init__(self, init, domain):
        self.init = init
        mem = Memory(width=32, depth=32, init=self.init)
        self.read_port = mem.read_port(domain="comb")
        self.write_port = mem.write_port(domain=domain, granularity=8)
        self.addr = Signal(32)
        self.rdata = self.read_port.data
        self.wmask = self.write_port.en
        self.wdata = self.write_port.data

    def elaborate(self, platform):
        m = Module()
        m.submodules.read_port = self.read_port
        m.submodules.write_port = self.write_port
        m.d.comb += [
            self.write_port.addr.eq(self.addr >> 2),
            self.read_port.addr.eq(self.addr >> 2),
        ]
        return m
