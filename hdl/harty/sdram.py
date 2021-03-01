from nmigen import *

from ..riscv import bus_layout

class SDRAM(Elaboratable):

    def __init__(self):
        self.bus = Record(bus_layout)
        

    def elaborate(self,platform):

        m = Module()

        comb = m.d.comb

        m.submodules.sdram = sdram = None

        comb += [
            self.bus.rdata.eq(
                Cat(
                    sdram.output.pll_locked,
                    sdram.output.mig_init_calib_complete,
                    sdram.output.app_rdy,
                )
            ),
        ]

        return m
