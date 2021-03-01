from nmigen import *
from nmigen.sim.core import *

from ..kitchensink.simplatform import SimPlatform
from ..kitchensink.uart import UART as llUART
from ..riscv import bus_layout


class UART(Elaboratable):
    def __init__(self, *, domain, freq):
        self._domain = domain
        self._freq = freq
        self.halt = False
        self.bus = Record(bus_layout)

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        if isinstance(platform, SimPlatform):
            m.submodules.uart = uart = llUART(self._domain, 4)

            def uart_sim_process():
                needs_lf = False
                while not self.halt:
                    uart_tx_rdy = yield uart.tx_rdy
                    if uart_tx_rdy:
                        uart_tx_data = yield uart.tx_data
                        char = chr(uart_tx_data & 0xFF)
                        print(char, end="")
                        needs_lf = char != "\n"
                    yield
                if needs_lf:
                    print()

            platform.add_sync_process(uart_sim_process, domain=self._domain)
        else:
            m.submodules.uart = uart = llUART(self._domain, round(self._freq / 115200))
            comb += platform.request("uart").tx.eq(uart.tx_o)

        comb += [
            self.bus.rdy.eq(1),
            self.bus.rdata.eq(uart.tx_ack),
            uart.tx_rdy.eq(self.bus.wmask.any()),
            uart.tx_data.eq(self.bus.wdata),
        ]

        return m