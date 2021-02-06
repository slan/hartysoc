from nmigen import *


class RAM(Elaboratable):
    def __init__(self, init, domain):
        self.init = init
        mem = Memory(width=32, depth=256, init=self.init)
        self.read_port = mem.read_port(domain = domain)
        self.write_port = mem.write_port(domain = domain, granularity=8)
        self.addr = Signal(32)
        self.data = Signal(32)
        self.err = Signal()
        self.wr_en = self.write_port.en
        self.wr_data = self.write_port.data


    def elaborate(self, platform):

        m = Module()
        m.submodules.read_port = self.read_port
        m.submodules.write_port = self.write_port
        m.d.comb += [
            # self.err.eq(self.addr >= (len(self.init) << 2)),
            self.read_port.addr.eq(self.addr),
            self.write_port.addr.eq(self.addr),
        ]

        return m
