from nmigen import *


class ROM(Elaboratable):
    def __init__(self, depth=128):
        mem = Memory(width=32, depth=depth)
        self.read_port = mem.read_port(domain="comb")
        self.addr = Signal(32)
        self.data = Signal(32)

    def set_content(self, content):
        self.read_port.memory.init = content

    def elaborate(self, platform):
        m = Module()

        m.submodules.read_port = self.read_port
        m.d.comb += [
            self.read_port.addr.eq(self.addr >> 2),
            self.data.eq(self.read_port.data),
        ]

        return m
