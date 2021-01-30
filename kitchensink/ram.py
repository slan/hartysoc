from nmigen import *


class RAM(Elaboratable):
    def __init__(self, init=None):
        self.init = init
        self.addr = Signal(32)
        self.data = Signal(32)

    def elaborate(self, platform):
        mem = Memory(width=32, depth=10, init=self.init)

        m = Module()
        m.submodules.read_port = read_port = mem.read_port()
        m.d.comb += [
            read_port.addr.eq(self.addr),
            self.data.eq(read_port.data),
        ]

        return m
