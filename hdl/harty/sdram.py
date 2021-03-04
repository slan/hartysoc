from nmigen.lib.fifo import AsyncFIFO
from hdl.kitchensink.simplatform import SimPlatform
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
        sync = m.d[self._domain]

        m.submodules.mig = mig = MIG()
        m.submodules.fifo_r = fifo_r = AsyncFIFO(
            width=32, depth=2, r_domain=self._domain, w_domain=mig.ui_domain
        )
        m.submodules.fifo_w = fifo_w = AsyncFIFO(
            width=32 + 26 + 1, depth=2, w_domain=self._domain, r_domain=mig.ui_domain
        )

        with m.If(self.bus.addr < 0x3000_0000):
            comb += [
                self.bus.rdy.eq(1),
                self.bus.rdata.eq(
                    Cat(
                        mig.pll_locked,
                        mig.mig_init_calib_complete,
                        mig.app_rdy,
                        mig.app_wdf_rdy,
                    )
                ),
            ]
        with m.Elif(mig.mig_init_calib_complete):
            with m.If(self.bus.wmask.any()):
                # BUS WRITE -> write to fifo_w, fire & forget
                comb += self.bus.rdy.eq(fifo_w.w_rdy)
                with m.If(fifo_w.w_rdy):
                    comb += [
                        fifo_w.w_en.eq(1),
                        fifo_w.w_data.eq(Cat(self.bus.wdata, self.bus.addr[0:26], 0)),
                    ]
            with m.If(self.bus.rmask.any()):
                # BUS READ -> write to fifo_w, lock the bus
                comb += self.bus.rdy.eq(0)
                with m.If(fifo_w.w_rdy):
                    in_flight = Signal()
                    sync += in_flight.eq(1)
                    with m.If(~in_flight):
                        comb += [
                            fifo_w.w_en.eq(1),
                            fifo_w.w_data.eq(Cat(Repl(0, 32), self.bus.addr[0:26], 1)),
                        ]
            with m.If(fifo_r.r_rdy):
                # Response from MIG -> read from fifo_r, release the bus
                comb += self.bus.rdy.eq(1)
                sync += in_flight.eq(0)
                comb += [
                    fifo_r.r_en.eq(1),
                    self.bus.rdata.eq(fifo_r.r_data),
                ]

        with m.If(fifo_w.r_rdy & mig.app_rdy & mig.app_wdf_rdy):
            # Execute command -> read from fifo_w
            comb += [
                fifo_w.r_en.eq(1),
                mig.app_en.eq(1),
                mig.app_cmd.eq(fifo_w.r_data[32 + 26]),
                mig.app_wdf_wren.eq(~fifo_w.r_data[32 + 26]),
                mig.app_wdf_data.eq(fifo_w.r_data[0:32]),
                mig.app_addr.eq(fifo_w.r_data[36 : 32 + 26]),
                mig.app_wdf_end.eq(1),
                mig.app_wdf_mask.eq(0),
            ]
        with m.If(mig.app_rd_data_valid & fifo_r.w_rdy):
            # Send read data -> write to fifo_r
            comb += [
                fifo_r.w_en.eq(1),
                fifo_r.w_data.eq(mig.app_rd_data),
            ]

        return m
