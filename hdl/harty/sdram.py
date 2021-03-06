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
                        fifo_w.w_data.eq(Cat(0, self.bus.addr[0:26], self.bus.wdata)),
                    ]
            with m.If(self.bus.rmask.any()):
                # BUS READ -> write to fifo_w, lock the bus
                comb += self.bus.rdy.eq(0)
                with m.If(fifo_w.w_rdy):
                    req_in_flight = Signal(1)
                    cd_hart += req_in_flight.eq(1)
                    with m.If(~req_in_flight):
                        comb += [
                            fifo_w.w_en.eq(1),
                            fifo_w.w_data.eq(Cat(1, self.bus.addr[0:26])),
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
        read_in_flight = Signal()
        with m.If(fifo_w.r_rdy & mig.app_rdy & mig.app_wdf_rdy):
            # Execute command -> read from fifo_w
            is_read = fifo_w.r_data[0]
            addr = fifo_w.r_data[1 : 1 + 26]
            data = fifo_w.r_data[1 + 26 : 1 + 26 + 32]
            # Since the bus is locked when reading, we know there can
            # be only one read request in flight.
            cd_mig += read_in_flight.eq(is_read)

            comb += [
                fifo_w.r_en.eq(1),
                mig.app_en.eq(1),
                mig.app_cmd.eq(is_read),
                mig.app_wdf_wren.eq(~is_read),
                mig.app_addr.eq(addr[1:]),  # addr is in memory words (16 bits)
                mig.app_wdf_end.eq(~is_read),
                mig.app_wdf_data.word_select(addr[2:4], 32).eq(data),
            ]
            with m.Switch(addr[2:4]):
                with m.Case(0b00):
                    comb += mig.app_wdf_mask.eq(0xFFF0)
                with m.Case(0b01):
                    comb += mig.app_wdf_mask.eq(0xFF0F)
                with m.Case(0b10):
                    comb += mig.app_wdf_mask.eq(0xF0FF)
                with m.Case(0b11):
                    comb += mig.app_wdf_mask.eq(0x0FFF)

        with m.If(mig.app_rd_data_valid & fifo_r.w_rdy):
            # Send read data back -> write to fifo_r
            # Ensure we're sending the response exactly once
            with m.If(read_in_flight):
                cd_mig += read_in_flight.eq(0)
                comb += [
                    fifo_r.w_en.eq(1),
                    fifo_r.w_data.eq(mig.app_rd_data),
                ]

        return m
