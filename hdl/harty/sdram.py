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


        m.submodules.mig = mig = MIG()
        m.submodules.fifo_r = fifo_r = AsyncFIFO(
            width=32, depth=2, r_domain=self._domain, w_domain=mig.ui_domain
        )
        m.submodules.fifo_w = fifo_w = AsyncFIFO(
            width=32 + 26 + 1, depth=2, w_domain=self._domain, r_domain=mig.ui_domain
        )

        comb = m.d.comb

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
        with m.Else():
            # HART domain: write to fifo_w, read from fifo_r
            cd_hart = m.d[self._domain]
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
                    req_in_flight = Signal(3)
                    cd_hart += req_in_flight.eq(Cat(self.bus.addr[2:4], 1))
                    with m.If(~req_in_flight.any()):
                        comb += [
                            fifo_w.w_en.eq(1),
                            fifo_w.w_data.eq(Cat(Repl(0, 32), self.bus.addr[0:26], 1)),
                        ]
            with m.If(fifo_r.r_rdy):
                # Response from MIG -> read from fifo_r, put data on the bus, release
                comb += self.bus.rdy.eq(1)
                cd_hart += req_in_flight.eq(0)
                comb += [
                    fifo_r.r_en.eq(1),
                    self.bus.rdata.eq(fifo_r.r_data),
                ]

        # MIG domain
        cd_mig = m.d[mig.ui_domain]
        rsp_in_flight = Signal()
        with m.If(fifo_w.r_rdy & mig.app_rdy & mig.app_wdf_rdy):
            # Execute command -> read from fifo_w
            is_read = fifo_w.r_data[32 + 26]
            data = fifo_w.r_data[0:32]
            addr = fifo_w.r_data[32 : 32 + 26]
            # Since the bus is locked when reading,
            # track the request so we send only 1 response
            cd_mig += rsp_in_flight.eq(is_read)

            comb += [
                fifo_w.r_en.eq(1),
                mig.app_en.eq(1),
                mig.app_cmd.eq(is_read),
                mig.app_wdf_wren.eq(~is_read),
                mig.app_wdf_data.eq(data),
                mig.app_addr.eq(addr),
                mig.app_wdf_end.eq(~is_read),
                mig.app_wdf_mask.eq(0xfff0),
            ]

        with m.If(mig.app_rd_data_valid & fifo_r.w_rdy):
            # Send read data back -> write to fifo_r

            with m.If(rsp_in_flight):
                cd_mig += rsp_in_flight.eq(0)
                comb += [
                    fifo_r.w_en.eq(1),
                    fifo_r.w_data.eq(mig.app_rd_data),
                ]

        return m
