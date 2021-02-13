from nmigen import *


class Registers(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        mem = Memory(width=32, depth=32)
        self.rp1 = mem.read_port(domain="comb")
        self.rp2 = mem.read_port(domain="comb")
        self.wp = mem.write_port(domain=domain)
        self.wr_en = Signal()
        self.wr_data = Signal(32)
        self.wr_idx = Signal(5)
        self.r1_idx = Signal(5)
        self.r2_idx = Signal(5)
        self.reg1 = Signal(32)
        self.reg2 = Signal(32)

    def elaborate(self, platform):
        m = Module()
        m.submodules.rp1 = self.rp1
        m.submodules.rp2 = self.rp2
        m.submodules.wp = self.wp

        comb = m.d.comb
        sync = m.d[self._domain]

        comb += [
            self.rp1.addr.eq(self.r1_idx),
            self.rp2.addr.eq(self.r2_idx),
            self.reg1.eq(self.rp1.data),
            self.reg2.eq(self.rp2.data),
            self.wp.addr.eq(self.wr_idx),
            self.wp.en.eq(self.wr_en & self.wr_idx.any()),
            self.wp.data.eq(self.wr_data),
        ]
        return m
