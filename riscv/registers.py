from nmigen import *


class Registers(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        self.wr_en = Signal()
        self.wr_data = Signal(32)
        self.wr_idx = Signal(5)
        self.r1_idx = Signal(5)
        self.r2_idx = Signal(5)
        self.reg1 = Signal(32)
        self.reg2 = Signal(32)

    def elaborate(self, platform):

        bank = Array(
            [
                Signal(32, name=f"x{i}")#, reset=0 if i == 0 else 0xDEADBEEF)
                for i in range(32)
            ]
        )
        self.bank = bank

        m = Module()
        comb = m.d.comb
        sync = m.d[self._domain]

        comb += [
            self.reg1.eq(bank[self.r1_idx]),
            self.reg2.eq(bank[self.r2_idx]),
        ]
        with m.If(self.wr_en & self.wr_idx.any()):  # don't write to x0
            sync += bank[self.wr_idx].eq(self.wr_data)

        return m
