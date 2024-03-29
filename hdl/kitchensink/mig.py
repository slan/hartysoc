from nmigen.build.dsl import Clock, Pins, Resource
from nmigen.hdl.rec import DIR_FANIN, DIR_FANOUT
from nmigen.sim.core import Passive, Settle, Tick
from .simplatform import SimPlatform
from .counter import Counter
from .pll import PLL
from nmigen import *


class MIG(Elaboratable):
    def __init__(self):
        self._domain = "mig_ui"
        # IN
        self.app_en = Signal(1)
        self.app_cmd = Signal(3)
        self.app_addr = Signal(28)
        self.app_wdf_data = Signal(128)
        self.app_wdf_end = Signal(1)
        self.app_wdf_wren = Signal(1)
        self.app_wdf_mask = Signal(16)
        # OUT
        self.mig_init_calib_complete = Signal(1)
        self.app_rd_data = Signal(128)
        self.app_rd_data_end = Signal(1)
        self.app_rd_data_valid = Signal(1)
        self.app_rdy = Signal(1)
        self.app_wdf_rdy = Signal(1)
        self.pll_locked = Signal(1)

    def elaborate(self, platform):

        m = Module()

        comb = m.d.comb

        m.submodules.pll = pll = PLL(
            mult=10,
            div=1,
            cd_specs={
                "sys": PLL.cd_spec(div=6, local=False),
                "ref": PLL.cd_spec(div=5, local=False),
            },
        )
        m.domains += ClockDomain(self._domain)

        comb += self.pll_locked.eq(pll.locked)

        if isinstance(platform, SimPlatform):
            platform.add_resources(
                [
                    Resource(
                        self._domain,
                        0,
                        Pins(self._domain, dir="i"),
                        Clock(
                            pll.get_frequency_ratio("sys")
                            * platform.default_clk_frequency
                            / 4
                        ),
                    )
                ]
            )

            mem = Memory(width=128, depth=8)
            m.submodules.mem_rp = mem_rp = mem.read_port(domain="comb")
            m.submodules.mem_wp = mem_wp = mem.write_port(
                domain=self._domain, granularity=8
            )

            def process():
                def _log(*values, **kwargs):
                    # print(*values, **kwargs)
                    pass

                yield Passive()
                while True:
                    locked = yield self.pll_locked
                    if locked:
                        yield self.mig_init_calib_complete.eq(1)
                        yield self.app_rdy.eq(1)
                        yield self.app_wdf_rdy.eq(1)
                        break

                while True:
                    app_en = yield self.app_en
                    if app_en:
                        app_cmd = yield self.app_cmd
                        app_addr = yield self.app_addr
                        _log(f"MIG cmd={app_cmd} addr={app_addr:#010x}", end="")
                        if app_cmd == 0:
                            app_wdf_data = yield self.app_wdf_data
                            app_wdf_mask = yield self.app_wdf_mask
                            _log(
                                f" wdf_data={app_wdf_data:#034x} wdf_mask={app_wdf_mask:#18b}"
                            )

                            yield mem_wp.addr.eq(self.app_addr[3:])
                            yield mem_wp.data.eq(self.app_wdf_data)
                            yield mem_wp.en.eq(~self.app_wdf_mask)
                            yield Settle()

                            mem_wp_addr = yield mem_wp.addr
                            mem_wp_data = yield mem_wp.data
                            mem_wp_en = yield mem_wp.en

                            _log(
                                f"-->   mem_addr={mem_wp_addr:#010x} mem_data={mem_wp_data:#034x}   mem_en={mem_wp_en:#018b}"
                            )
                        elif app_cmd == 1:
                            yield mem_rp.addr.eq(self.app_addr[3:])
                            yield Settle()
                            yield self.app_rd_data.eq(
                                mem_rp.data.word_select((app_addr & 0b110) >> 1, 32)
                            )
                            yield self.app_rd_data_valid.eq(1)
                            yield Settle()

                            mem_rp_addr = yield mem_rp.addr
                            mem_rp_data = yield mem_rp.data
                            app_rd_data = yield self.app_rd_data
                            _log()
                            _log(
                                f"<--   mem_addr={mem_rp_addr:#010x} mem_data={mem_rp_data:#034x}"
                            )
                            _log(
                                f"                          app_data={app_rd_data:#034x}"
                            )
                        else:
                            raise Exception(f"Unknown cmd {app_cmd}")
                        _log()

                    yield

            platform.add_sync_process(process, domain=self._domain)

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
                o_ui_clk=ClockSignal(self._domain),
                o_ui_clk_sync_rst=ResetSignal(self._domain),
                i_app_wdf_mask=self.app_wdf_mask,
                i_sys_clk_i=ClockSignal("sys"),
                i_clk_ref_i=ClockSignal("ref"),
                i_sys_rst=~ResetSignal("sys"),
            )

        return m
