from nmigen import *
from nmigen.lib.fifo import AsyncFIFO

from ..kitchensink import MIG
from ..riscv import bus_layout


class SDRAM(Elaboratable):
    """A bus adapter to Xilinx's memory controller (MIG).

    Using 2 async FIFOs to cross clock domains.

    FIFO message format
    -------------------

    bits    | 61 30 | 29 4 | 3   0
    content | wdata | addr | wmask
    width   |    32 |   26 |     4

    Parameters
    ----------
    domain: str
        Clock domain of the bus.
    """

    def __init__(self, domain):
        self._domain = domain
        self.bus = Record(bus_layout, name="sdram")

    def elaborate(self, platform):

        m = Module()

        m.submodules.mig = mig = MIG()
        m.submodules.fifo_mig = fifo_mig = AsyncFIFO(
            width=32 + 26 + 4,
            depth=2,
            w_domain=self._domain,
            r_domain=mig._domain,
        )
        m.submodules.fifo_hart = fifo_hart = AsyncFIFO(
            width=32,
            depth=2,
            r_domain=self._domain,
            w_domain=mig._domain,
        )

        comb = m.d.comb

        # HART domain: write to fifo_mig, read from fifo_hart
        #
        with m.FSM(domain=self._domain):
            with m.State("WAIT"):
                with m.If(fifo_mig.w_rdy):
                    with m.If(self.bus.wmask.any()):
                        # BUS WRITE -> write to fifo_mig, lock the bus
                        comb += [
                            fifo_mig.w_en.eq(1),
                            fifo_mig.w_data.eq(
                                Cat(self.bus.wmask, self.bus.addr[0:26], self.bus.wdata)
                            ),
                        ]
                        m.next = "WACK"
                    with m.Elif(self.bus.rmask.any()):
                        # BUS READ -> write to fifo_mig, lock the bus
                        comb += [
                            fifo_mig.w_en.eq(1),
                            fifo_mig.w_data.eq(Cat(0, 0, 0, 0, self.bus.addr[0:26])),
                        ]
                        m.next = "RACK"
            with m.State("WACK"):
                # Write command send to the MIG -> release the bus
                comb += self.bus.ack.eq(1)
                m.next = "WAIT"
            with m.State("RACK"):
                with m.If(fifo_hart.r_rdy):
                    # Read command response from MIG -> read from fifo_hart, put data on the bus, release
                    comb += [
                        self.bus.ack.eq(1),
                        fifo_hart.r_en.eq(1),
                        self.bus.rdata.eq(fifo_hart.r_data),
                    ]
                    m.next = "WAIT"

        # MIG domain: write to fifo_hart, read from fifo_mig
        #
        with m.FSM(domain=mig._domain):
            with m.State("WAIT"):
                with m.If(fifo_mig.r_rdy & mig.app_rdy & mig.app_wdf_rdy):
                    # Execute command -> read from fifo_mig
                    wmask = fifo_mig.r_data[0:4]
                    is_write = wmask.any()
                    addr = fifo_mig.r_data[4 : 4 + 26]
                    data = fifo_mig.r_data[4 + 26 : 4 + 26 + 32]

                    comb += [
                        fifo_mig.r_en.eq(1),
                        mig.app_en.eq(1),
                        mig.app_cmd.eq(~is_write),
                        mig.app_wdf_wren.eq(is_write),
                        mig.app_addr.eq(addr[1:]),  # addr is in memory words (16 bits)
                        mig.app_wdf_end.eq(is_write),
                        mig.app_wdf_data.word_select(addr[2:4], 32).eq(data),
                    ]
                    with m.Switch(addr[2:4]):
                        with m.Case(0b00):
                            comb += mig.app_wdf_mask.eq(Cat(~wmask, 0xFFF))
                        with m.Case(0b01):
                            comb += mig.app_wdf_mask.eq(Cat(0xF, ~wmask, 0xFF))
                        with m.Case(0b10):
                            comb += mig.app_wdf_mask.eq(Cat(0xFF, ~wmask, 0xF))
                        with m.Case(0b11):
                            comb += mig.app_wdf_mask.eq(Cat(0xFFF, ~wmask))

                    with m.If(~is_write):
                        m.next = "READ"
            with m.State("READ"):
                with m.If(mig.app_rd_data_valid & fifo_hart.w_rdy):
                    # Send read data back -> write to fifo_hart
                    comb += [
                        fifo_hart.w_en.eq(1),
                        fifo_hart.w_data.eq(mig.app_rd_data),
                    ]
                    m.next = "WAIT"

        return m
