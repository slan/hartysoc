from nmigen import *


class Core(Elaboratable):
    def __init__(self, rom):
        self.pc = Signal(32)
        self.instr = Signal(32)
        self.rom = rom

    def elaborate(self, platform):
        max_value = int(platform.default_clk_frequency - 4)
        counter = Signal(range(max_value))
        m = Module()

        with m.FSM():
            with m.State("FETCH"):
                m.d.comb += self.rom.addr.eq(self.pc)
                m.next="DECODE"
            with m.State("DECODE"):
                m.d.sync += self.instr.eq(self.rom.data)
                m.next="EXECUTE"
            with m.State("EXECUTE"):
                m.d.sync += self.pc.eq(Mux(self.pc == self.rom.len - 1, 0, self.pc + 1))
                m.d.sync += counter.eq(0)
                m.next = "WAIT"
            with m.State("WAIT"):
                with m.If(counter == max_value):
                    m.next = "FETCH"
                with m.Else():
                    m.d.sync += counter.eq(counter + 1)

        return m
        