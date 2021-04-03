from nmigen import *
from nmigen.lib.fifo import AsyncFIFO
from nmigen.sim.core import Passive
from ..riscv.bus import bus_layout

from ..kitchensink.simplatform import SimPlatform


class SPI(Elaboratable):
    def __init__(self, *, domain):
        self._domain = domain
        self.bus = Record(bus_layout, name="spi")

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        sync = m.d.sync

        if isinstance(platform, SimPlatform):
            spi = Record([("cipo", 1), ("copi", 1), ("cs", 1), ("clk", 1)])

            def spi_process():
                yield Passive()
                while True:
                    if (yield spi.cs):
                        cmd = 0
                        for i in range(8):
                            cmd = (cmd << 1) | (yield spi.copi)
                            yield
                        print(f"{cmd:#04x}")
                        cmd = 0x81
                        while (yield spi.cs):
                            for i in range(8):
                                yield spi.cipo.eq((cmd & (1 << (7 - i))) >> (7 - i))
                                yield
                            cmd += 1
                    yield

            platform.add_sync_process(spi_process, domain=sync._domain)
        else:
            spi = platform.request("spi_flash_1x")

        m.submodules.fifo_hart = fifo_hart = AsyncFIFO(
            width=8, depth=2, r_domain=sync._domain, w_domain=self._domain
        )
        m.submodules.fifo_spi = fifo_spi = AsyncFIFO(
            width=8, depth=32, r_domain=self._domain, w_domain=sync._domain
        )

        with m.If(self.bus.wmask.any() & fifo_hart.w_rdy):
            comb += [
                fifo_hart.w_en.eq(1),
                fifo_hart.w_data.eq(self.bus.wdata),
                self.bus.ack.eq(1),
            ]
        with m.If(self.bus.rmask.any() & fifo_spi.r_rdy):
            comb += [
                fifo_spi.r_en.eq(1),
                self.bus.rdata.eq(fifo_spi.r_data),
                self.bus.ack.eq(1),
            ]

        cmd = Signal(8)
        bits = Signal(3)
        rx_valid = Signal()
        to_read = Signal(range(20))
        dummy_cycles = Signal()

        with m.If(to_read.any()):
            comb += [
                spi.cs.eq(1),
                spi.clk.eq(~ClockSignal(sync._domain)),
            ]

        with m.FSM(domain=sync._domain):
            with m.State("WAIT"):
                with m.If(fifo_hart.r_rdy):
                    comb += fifo_hart.r_en.eq(1)
                    sync += [
                        cmd.eq(fifo_hart.r_data),
                        to_read.eq(20),
                    ]
                    m.next = "TRANSMIT"
            with m.State("TRANSMIT"):
                comb += spi.copi.eq(cmd[7])
                sync += [
                    bits.eq(bits + 1),
                    cmd.eq(Cat(0, cmd)),
                ]
                with m.If(bits.all()):
                    sync += dummy_cycles.eq(1)
                    m.next = "RECEIVE"
            with m.State("RECEIVE"):
                with m.If(dummy_cycles.any()):
                    sync += dummy_cycles.eq(dummy_cycles - 1)
                with m.Else():
                    sync += [
                        rx_valid.eq(1),
                        bits.eq(bits + 1),
                        cmd.eq(Cat(spi.cipo, cmd)),
                    ]
                    with m.If(~bits.any() & rx_valid):  # Don't ack initial bits==0 (nothing but dummy received yet)
                        with m.If(fifo_spi.w_rdy):
                            comb += [
                                fifo_spi.w_en.eq(1),
                                fifo_spi.w_data.eq(cmd),
                            ]
                        sync += to_read.eq(to_read - 1)
                with m.If(~spi.cs):
                    m.next = "WAIT"

        return m
