from nmigen import *
from nmigen.sim.core import *

from ..kitchensink.simplatform import SimPlatform
from ..kitchensink.uart import UART
from ..riscv import bus_layout


class Console(Elaboratable):
    def __init__(self, *, domain, domain_freq):
        self._domain = domain
        self._domain_freq = domain_freq
        self.last_output = 0
        self.bus = Record(bus_layout)

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        if isinstance(platform, SimPlatform):
            comb += [
                self.bus.rdy.eq(1),
                self.bus.rdata.eq(1),
            ]
            def uart_sim_process():
                yield Passive()
                while True:
                    yield
                    uart_tx_rdy = yield self.bus.wmask.any()
                    if uart_tx_rdy:
                        uart_tx_data = yield self.bus.wdata
                        self.last_output = chr(uart_tx_data & 0xFF)
                        print(self.last_output, end="")
            platform.add_sync_process(uart_sim_process, domain=self._domain)
        else:
            m.submodules.uart = uart = UART(self._domain, round(self._domain_freq / 115200))
            comb += platform.request("uart").tx.eq(uart.tx_o)

            comb += [
                self.bus.rdy.eq(1),
                self.bus.rdata.eq(uart.tx_ack),
                uart.tx_rdy.eq(self.bus.wmask.any()),
                uart.tx_data.eq(self.bus.wdata),
            ]

        return m