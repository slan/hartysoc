from nmigen.build.dsl import Clock, Pins, Resource
from nmigen.hdl.rec import DIR_FANIN, DIR_FANOUT
from .simplatform import SimPlatform
from .counter import Counter
from .pll import PLL
from nmigen import *


output_layout = [
    ("mig_init_calib_complete", 1, DIR_FANOUT),
    ("app_rd_data", 128, DIR_FANOUT),
    ("app_rd_data_end", 1, DIR_FANOUT),
    ("app_rd_data_valid", 1, DIR_FANOUT),
    ("app_rdy", 1, DIR_FANOUT),
    ("app_wdf_rdy", 1, DIR_FANOUT),
    ("pll_locked", 1, DIR_FANOUT),
]
input_layout = [
    ("app_addr", 28, DIR_FANIN),
    ("app_cmd", 3, DIR_FANIN),
    ("app_en", 1, DIR_FANIN),
    ("app_wdf_data", 128, DIR_FANIN),
    ("app_wdf_end", 1, DIR_FANIN),
    ("app_wdf_wren", 1, DIR_FANIN),
    ("app_wdf_mask", 16, DIR_FANIN),
]


class MIG(Elaboratable):
    def __init__(self):
        self.ui_domain = "mig"
        self.input = Record(input_layout)
        self.output = Record(output_layout)

    def elaborate(self, platform):
        m = Module()

        comb = m.d.comb

        m.submodules.pll = pll = PLL(
            mult=10,
            div=1,
            domains={
                "sys": 6,
                "ref": 5,
            },
        )
        m.domains += ClockDomain(self.ui_domain)

        comb += self.output.pll_locked.eq(pll.locked)

        if isinstance(platform, SimPlatform):
            platform.add_resources(
                [
                    Resource(
                        self.ui_domain,
                        0,
                        Pins(self.ui_domain, dir="i"),
                        Clock(
                            platform.default_clk_frequency
                            * pll.get_frequency_ratio("sys")
                            / 4
                        ),
                    )
                ]
            )
            comb += [
                self.output.pll_locked.eq(1),
                self.output.mig_init_calib_complete.eq(1),
                self.output.app_rdy.eq(1),
                self.output.app_wdf_rdy.eq(1),
            ]
            with m.If(self.input.app_en & self.input.app_wdf_wren & self.input.app_cmd[0]):
                comb += [
                    self.output.app_rd_data.eq(0x1234),
                    self.output.app_rd_data_valid.eq(1),
                    self.output.app_rd_data_end.eq(1),
                ]

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
                o_init_calib_complete=self.output.mig_init_calib_complete,
                o_ddr3_cs_n=ddr3.cs,
                o_ddr3_dm=ddr3.dm,
                o_ddr3_odt=ddr3.odt,
                i_app_addr=self.input.app_addr,
                i_app_cmd=self.input.app_cmd,
                i_app_en=self.input.app_en,
                i_app_wdf_data=self.input.app_wdf_data,
                i_app_wdf_end=self.input.app_wdf_end,
                i_app_wdf_wren=self.input.app_wdf_wren,
                o_app_rd_data=self.output.app_rd_data,
                o_app_rd_data_end=self.output.app_rd_data_end,
                o_app_rd_data_valid=self.output.app_rd_data_valid,
                o_app_rdy=self.output.app_rdy,
                o_app_wdf_rdy=self.output.app_wdf_rdy,
                i_app_sr_req=Const(0),
                i_app_ref_req=Const(0),
                i_app_zq_req=Const(0),
                o_app_sr_active=Signal(1, name="app_sr_active"),
                o_app_ref_ack=Signal(1, name="app_ref_ack"),
                o_app_zq_ack=Signal(1, name="app_zq_ack"),
                o_ui_clk=ClockSignal(self.ui_domain),
                o_ui_clk_sync_rst=ResetSignal(self.ui_domain),
                i_app_wdf_mask=self.input.app_wdf_mask,
                i_sys_clk_i=ClockSignal("sys"),
                i_clk_ref_i=ClockSignal("ref"),
                i_sys_rst=~ResetSignal("sys"),
            )

        return m
