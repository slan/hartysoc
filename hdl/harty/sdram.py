from nmigen import *

from ..riscv import bus_layout
from ..kitchensink import MIG


class SDRAM(Elaboratable):
    def __init__(self, domain):
        self._domain = domain
        self.bus = Record(bus_layout)

    def elaborate(self, platform):

        m = Module()

        comb = m.d.comb

        m.submodules.mig = mig = MIG(self._domain)

        comb += [
            self.bus.rdy.eq(1),
            self.bus.rdata.eq(
                Cat(
                    mig.output.pll_locked,
                    mig.output.mig_init_calib_complete,
                    mig.output.app_rdy,
                )
            ),
        ]

        return m
