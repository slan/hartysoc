from nmigen import *


class RAM(Elaboratable):
    def __init__(self, depth, domain):
        mem = Memory(width=32, depth=depth)
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
        with m.If(self.wmask.any()):
            m.d.comb += self.write_port.addr.eq(self.addr >> 2)
        with m.Else():
            m.d.comb += self.read_port.addr.eq(self.addr >> 2)

        return m
