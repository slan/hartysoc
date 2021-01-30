from nmigen import  *
from nmigen.lib.cdc import ResetSynchronizer


class SDRAM(Elaboratable):
    def __init__(self):
        self.top_signal = Signal(1, name="top_signal")

    def elaborate(self, platform):
        m = Module()

        clk_fb = Signal()
        pll_locked = Signal()

        m.submodules.pll = Instance(
            "PLLE2_BASE",
            p_BANDWIDTH="OPTIMIZED",  # OPTIMIZED, HIGH, LOW
            # Multiply value for all CLKOUT, (2-64)
            p_CLKFBOUT_MULT=10,
            # Phase offset in degrees of CLKFB, (-360.000-360.000).
            p_CLKFBOUT_PHASE=0.0,
            # Input clock period in ns to ps resolution (i.e. 33.333 is 30 MHz).
            p_CLKIN1_PERIOD=1e9 / platform.default_clk_frequency,
            # CLKOUT0_DIVIDE - CLKOUT5_DIVIDE: Divide amount for each CLKOUT (1-128)
            p_CLKOUT0_DIVIDE=6,
            p_CLKOUT1_DIVIDE=5,
            # CLKOUT0_DUTY_CYCLE - CLKOUT5_DUTY_CYCLE: Duty cycle for each CLKOUT (0.001-0.999).
            p_CLKOUT0_DUTY_CYCLE=0.5,
            p_CLKOUT1_DUTY_CYCLE=0.5,
            # CLKOUT0_PHASE - CLKOUT5_PHASE: Phase offset for each CLKOUT (-360.000-360.000).
            p_CLKOUT0_PHASE=0.0,
            p_CLKOUT1_PHASE=0.0,
            p_DIVCLK_DIVIDE=1,  # Master division value, (1-56)
            # Reference input jitter in UI, (0.000-0.999).
            p_REF_JITTER1=0.0,
            # Delay DONE until PLL Locks, ('TRUE'/'FALSE')
            p_STARTUP_WAIT="TRUE",
            # Clock Outputs: 1-bit (each) output: User configurable clock outputs
            o_CLKOUT0=ClockSignal("sys"),  # 1-bit output: CLKOUT1
            o_CLKOUT1=ClockSignal("ref"),  # 1-bit output: CLKOUT0
            # Feedback Clocks: 1-bit (each) output: Clock feedback ports
            o_CLKFBOUT=clk_fb,  # 1-bit output: Feedback clock
            o_LOCKED=pll_locked,  # 1-bit output: LOCK
            i_CLKIN1=ClockSignal(),  # 1-bit input: Input clock
            # Control Ports: 1-bit (each) input: PLL control ports
            i_PWRDWN=Const(0),  # 1-bit input: Power-down
            i_RST=ResetSignal(),  # 1-bit input: Reset
            # Feedback Clocks: 1-bit (each) input: Clock feedback ports
            i_CLKFBIN=clk_fb,  # 1-bit input: Feedback clock
        )

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

        mig_init_calib_complete = Signal()
        mig_ui_clk_sync_rst = Signal()

        app_addr = Signal(28)
        app_cmd = Signal(3)
        app_en = Signal()
        app_wdf_data = Signal(128)
        app_wdf_end = Signal()
        app_wdf_wren = Signal()
        app_rd_data = Signal(128)
        app_rd_data_end = Signal()
        app_rd_data_valid = Signal()
        app_rdy = Signal()
        app_wdf_rdy = Signal()
        app_wdf_mask = Signal(16)

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
            o_init_calib_complete=mig_init_calib_complete,
            o_ddr3_cs_n=ddr3.cs,
            o_ddr3_dm=ddr3.dm,
            o_ddr3_odt=ddr3.odt,
            i_app_addr=app_addr,
            i_app_cmd=app_cmd,
            i_app_en=app_en,
            i_app_wdf_data=app_wdf_data,
            i_app_wdf_end=app_wdf_end,
            i_app_wdf_wren=app_wdf_wren,
            o_app_rd_data=app_rd_data,
            o_app_rd_data_end=app_rd_data_end,
            o_app_rd_data_valid=app_rd_data_valid,
            o_app_rdy=app_rdy,
            o_app_wdf_rdy=app_wdf_rdy,
            i_app_sr_req=Const(0),
            i_app_ref_req=Const(0),
            i_app_zq_req=Const(0),
            o_app_sr_active=Signal(1, name="app_sr_active"),
            o_app_ref_ack=Signal(1, name="app_ref_ack"),
            o_app_zq_ack=Signal(1, name="app_zq_ack"),
            o_ui_clk=ClockSignal("ui"),
            o_ui_clk_sync_rst=mig_ui_clk_sync_rst,
            i_app_wdf_mask=app_wdf_mask,
            i_sys_clk_i=ClockSignal("sys"),
            i_clk_ref_i=ClockSignal("ref"),
            i_sys_rst=~ResetSignal("sys"),
        )

        combined_rst = ResetSignal() | ~pll_locked

        m.submodules.rs_sys = ResetSynchronizer(combined_rst, domain="sys")
        m.submodules.rs_ref = ResetSynchronizer(combined_rst, domain="ref")
        m.submodules.rs_ui = ResetSynchronizer(
            mig_init_calib_complete & mig_ui_clk_sync_rst, domain="ui"
        )

        m.domains += [ClockDomain("ref"), ClockDomain("sys"), ClockDomain("ui")]

        data = Signal(128)

        with m.FSM(domain="ui"):
            with m.State("WAIT_WRDY"):
                with m.If(app_rdy & app_wdf_rdy):
                    m.d.ui += app_cmd.eq(0)  # write
                    m.d.ui += app_addr.eq(0)
                    m.d.ui += app_en.eq(1)
                    m.d.ui += app_wdf_data.eq(
                        0x32345678_90ABCDEF_FEDCBA09_87654322
                    )  # 123456789abcdef0123456789abcde5)
                    m.d.ui += app_wdf_mask.eq(0)
                    m.d.ui += app_wdf_wren.eq(1)
                    m.d.ui += app_wdf_end.eq(1)
                    m.next = "WAIT_WACK"
            with m.State("WAIT_WACK"):
                with m.If(app_rdy):
                    m.d.ui += app_en.eq(0)
                    m.d.ui += app_wdf_wren.eq(0)
                    m.next = "WAIT_RRDY"
            with m.State("WAIT_RRDY"):
                with m.If(app_rdy):
                    m.d.ui += app_cmd.eq(1)  # read
                    m.d.ui += app_addr.eq(0)
                    m.d.ui += app_en.eq(1)
                    m.next = "WAIT_RACK"
            with m.State("WAIT_RACK"):
                with m.If(app_rdy):
                    m.d.ui += app_en.eq(0)
                    with m.If(app_rd_data_valid):
                        m.d.ui += data.eq(app_rd_data)
                        m.next = "DONE"
            with m.State("DONE"):
                pass

        return m
