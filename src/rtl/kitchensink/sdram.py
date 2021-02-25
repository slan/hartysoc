from .simplatform import SimPlatform
from .counter import Counter
from .pll import PLL
from nmigen import *


class SDRAM(Elaboratable):
    def __init__(self):
        self.mig_init_calib_complete = Signal()

        self.app_addr = Signal(28)
        self.app_cmd = Signal(3)
        self.app_en = Signal()
        self.app_wdf_data = Signal(128)
        self.app_wdf_end = Signal()
        self.app_wdf_wren = Signal()
        self.app_rd_data = Signal(128)
        self.app_rd_data_end = Signal()
        self.app_rd_data_valid = Signal()
        self.app_rdy = Signal()
        self.app_wdf_rdy = Signal()
        self.app_wdf_mask = Signal(16)
        self.pll_locked = Signal()

    def elaborate(self, platform):
        m = Module()

        m.submodules.pll = pll = PLL(
            mult=10,
            div=1,
            domains={
                "sys": 6,
                "ref": 5,
            },
        )

        m.d.comb += self.pll_locked.eq(pll.locked)

        if isinstance(platform, SimPlatform):
            m.submodules.cnt = cnt = Counter(255)
            m.d.sync += self.app_rdy.eq(cnt._counter[7])
        else:
            ddr3 = platform.request(
                "ddr3",
                dir={
                    "rst": "-",
                    "clk": "-",
                    "clk_en": "-",
                    "cs": "-",
                    "we": "-",
                    "ras": "-",
                    "cas": "-",
                    "a": "-",
                    "ba": "-",
                    "dqs": "-",
                    "dq": "-",
                    "dm": "-",
                    "odt": "-",
                },
            )

            m.submodules.mig = Instance(
                "mig_7series_0",
                o_ddr3_addr=ddr3.a,
                o_ddr3_ba=ddr3.ba,
                o_ddr3_cas_n=ddr3.cas,
                o_ddr3_ck_n=ddr3.clk.n,
                o_ddr3_ck_p=ddr3.clk.p,
                o_ddr3_cke=ddr3.clk_en,
                o_ddr3_ras_n=ddr3.ras,
                o_ddr3_reset_n=ddr3.rst,
                o_ddr3_we_n=ddr3.we,
                io_ddr3_dq=ddr3.dq,
                io_ddr3_dqs_n=ddr3.dqs.n,
                io_ddr3_dqs_p=ddr3.dqs.p,
                o_init_calib_complete=self.mig_init_calib_complete,
                o_ddr3_cs_n=ddr3.cs,
                o_ddr3_dm=ddr3.dm,
                o_ddr3_odt=ddr3.odt,
                i_app_addr=self.app_addr,
                i_app_cmd=self.app_cmd,
                i_app_en=self.app_en,
                i_app_wdf_data=self.app_wdf_data,
                i_app_wdf_end=self.app_wdf_end,
                i_app_wdf_wren=self.app_wdf_wren,
                o_app_rd_data=self.app_rd_data,
                o_app_rd_data_end=self.app_rd_data_end,
                o_app_rd_data_valid=self.app_rd_data_valid,
                o_app_rdy=self.app_rdy,
                o_app_wdf_rdy=self.app_wdf_rdy,
                i_app_sr_req=Const(0),
                i_app_ref_req=Const(0),
                i_app_zq_req=Const(0),
                o_app_sr_active=Signal(1, name="app_sr_active"),
                o_app_ref_ack=Signal(1, name="app_ref_ack"),
                o_app_zq_ack=Signal(1, name="app_zq_ack"),
                o_ui_clk=ClockSignal("ui"),
                o_ui_clk_sync_rst=ResetSignal("ui"),
                i_app_wdf_mask=self.app_wdf_mask,
                i_sys_clk_i=ClockSignal("sys"),
                i_clk_ref_i=ClockSignal("ref"),
                i_sys_rst=~ResetSignal("sys"),
            )

        m.domains += ClockDomain("ui")

        return m
