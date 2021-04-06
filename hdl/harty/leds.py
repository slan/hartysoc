from nmigen import *

from ..riscv.bus import bus_layout


class LEDs(Elaboratable):
    def __init__(self, *, divisor, domain):
        self._domain = domain
        self._divisor = divisor
        self.bus = Record(bus_layout)

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb
        sync = m.d[self._domain]

        m.domains.led = cd_led = ClockDomain("led")


        phase = Signal(range(self._divisor))

        with m.If(phase==0):
            sync += [
                phase.eq(self._divisor),
                cd_led.clk.eq(~cd_led.clk),
            ]
        with m.Else():
            sync += phase.eq(phase-1)

        foo = Signal()
        m.d[cd_led.name] += foo.eq(~foo)

        leds = Signal(4)

        comb += self.bus.ack.eq(1)
        
        with m.If(self.bus.rmask.any()):
            comb += self.bus.rdata.eq(leds)

        with m.Elif(self.bus.wmask.any()):
            sync += leds.eq(self.bus.wdata)

        comb += [platform.request("led", i).o.eq(leds[i]) for i in range(leds.width)]

        return m
