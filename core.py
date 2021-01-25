from nmigen import Elaboratable, Module, Mux, Signal


class Core(Elaboratable):
    def __init__(self, data_len):
        self.pc = Signal(32)
        self.instr = Signal(32)
        self.stage = Signal(2)
        self.addr = Signal(32)
        self.data = Signal(32)
        self.data_len = data_len
        self.counter = Signal(25)

    def elaborate(self, platform):
        m = Module()

        with m.If(self.stage == 0):
            m.d.sync += self.addr.eq(self.pc)
            m.d.sync += self.stage.eq(1)
        with m.If(self.stage == 1):
            m.d.sync += self.instr.eq(self.data)
            m.d.sync += self.stage.eq(2)
        with m.If(self.stage == 2):
            m.d.sync += self.pc.eq(Mux(self.pc == self.data_len - 1, 0, self.pc + 1))
            m.d.sync += self.counter.eq(
                int(platform.default_clk_frequency - 1) if platform is not None else 0
            )
            m.d.sync += self.stage.eq(3)
        with m.If(self.stage == 3):
            with m.If(self.counter == 0):
                m.d.sync += self.stage.eq(0)
            with m.Else():
                m.d.sync += self.counter.eq(self.counter - 1)

        return m

    def ports(self):
        return [self.pc, self.instr]
