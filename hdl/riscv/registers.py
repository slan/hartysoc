from nmigen import *


class Registers(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        mem = Memory(width=32, depth=32)
        self._rp1 = mem.read_port(domain="comb")
        self._rp2 = mem.read_port(domain="comb")
        self._wp = mem.write_port(domain=domain)
        self.rs1_addr = self._rp1.addr
        self.rs1_rdata = Mux(self.rs1_addr.any(), self._rp1.data, 0)
        self.rs2_addr = self._rp2.addr
        self.rs2_rdata = Mux(self.rs2_addr.any(), self._rp2.data, 0)
        self.rd_addr = self._wp.addr
        self.rd_wdata = self._wp.data

    def elaborate(self, platform):
        m = Module()

        m.submodules.rp1 = self._rp1
        m.submodules.rp2 = self._rp2
        m.submodules.wp = self._wp

        m.d.comb += self._wp.en.eq(self.rd_addr.any())

        return m
