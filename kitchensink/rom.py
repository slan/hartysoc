from nmigen import *


class ROM(Elaboratable):
    def __init__(self, init=None, domain_name="sync"):
        self.init = init
        self.domain_name = domain_name
        self.addr = Signal(32)
        self.data = Signal(32)
        self.err = Signal()

    def elaborate(self, platform):
        mem = Memory(width=32, depth=10, init=self.init)

        m = Module()
        m.submodules.read_port = read_port = mem.read_port()
        m.d[self.domain_name] += self.err.eq(self.addr >= (len(self.init) << 2)),
        m.d.comb += [
            read_port.addr.eq(self.addr >> 2),
            self.data.eq(read_port.data),
        ]

        return m
