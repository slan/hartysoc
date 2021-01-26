import sys

from nmigen import *
from nmigen.build import *
from nmigen_boards.arty_a7 import ArtyA7Platform
from kitchensink import *


class RAM(Elaboratable):
    def __init__(self):
        self.top_signal = Signal(1, name="top_signal")

    def elaborate(self, platform):
        m = Module()

        clk_fb = Signal()
        pll_locked = Signal()

        m.domains += [ClockDomain("ref"), ClockDomain("sys"), ClockDomain("ui")]

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

        calib = Signal()
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
            o_init_calib_complete=calib,
            o_ddr3_cs_n=ddr3.cs,
            o_ddr3_dm=ddr3.dm,
            o_ddr3_odt=ddr3.odt,
            i_app_addr=Const(0),
            i_app_cmd=Const(0),
            i_app_en=Const(0),
            i_app_wdf_data=Const(0),
            i_app_wdf_end=Const(0),
            i_app_wdf_wren=Const(0),
            o_app_rd_data=Signal(128, name="app_rd_data"),
            o_app_rd_data_end=Signal(1, name="app_rd_data_end"),
            o_app_rd_data_valid=Signal(1, name="app_rd_data_valid"),
            o_app_rdy=Signal(1, name="app_rdy"),
            o_app_wdf_rdy=Signal(1, name="app_wdf_rdy"),
            i_app_sr_req=Const(0),
            i_app_ref_req=Const(0),
            i_app_zq_req=Const(0),
            o_app_sr_active=Signal(1, name="app_sr_active"),
            o_app_ref_ack=Signal(1, name="app_ref_ack"),
            o_app_zq_ack=Signal(1, name="app_zq_ack"),
            o_ui_clk=ClockSignal("ui"),
            o_ui_clk_sync_rst=Signal(1, name="ui_clk_sync_rst"),
            i_app_wdf_mask=Const(0),
            i_sys_clk_i=ClockSignal("sys"),
            i_clk_ref_i=ClockSignal("ref"),
            i_sys_rst=pll_locked,
        )

        counter_ui = Counter(int(500e6 / 6) - 1, "ui")      #  83.333 MHz
        counter_sync = Counter(int(100e6) - 1, "sync")      # 100.000 MHz
        counter_sys = Counter(int(500e6 / 3) - 1, "sys")    # 166.666 MHz
        counter_ref = Counter(int(200e6) - 1, "ref")        # 200.000 MHz

        m.submodules += [counter_ui, counter_sync, counter_sys, counter_ref]

        m.d.comb += platform.request("led", 0).eq(counter_ui.out)
        m.d.comb += platform.request("led", 1).eq(counter_sync.out)
        m.d.comb += platform.request("led", 2).eq(counter_sys.out)
        m.d.comb += platform.request("led", 3).eq(counter_ref.out)

        return m


if __name__ == "__main__":

    top = RAM()

    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == "sim":

        def process():
            for _ in range(10):
                yield

        platform = SimPlatform()
        platform.add_sync_process(process)
        additional_resources = [
            Resource("led", 0, Pins("led0", dir="o")),
            Resource("led", 1, Pins("led1", dir="o")),
            Resource("led", 2, Pins("led2", dir="o")),
            Resource("led", 3, Pins("led3", dir="o")),
        ]
    elif platform_name == "arty":
        platform = ArtyA7Platform()
        additional_resources = [
            Resource(
                "vgapmod",
                0,
                Subsignal(
                    "hsync",
                    Pins("7", dir="o", conn=("pmod", 2)),
                    Attrs(IOSTANDARD="LVCMOS33"),
                ),
                Subsignal(
                    "vsync",
                    Pins("8", dir="o", conn=("pmod", 2)),
                    Attrs(IOSTANDARD="LVCMOS33"),
                ),
                Subsignal(
                    "r",
                    Pins("1 2 3 4", dir="o", conn=("pmod", 1)),
                    Attrs(IOSTANDARD="LVCMOS33"),
                ),
                Subsignal(
                    "g",
                    Pins("1 2 3 4", dir="o", conn=("pmod", 2)),
                    Attrs(IOSTANDARD="LVCMOS33"),
                ),
                Subsignal(
                    "b",
                    Pins("7 8 9 10", dir="o", conn=("pmod", 1)),
                    Attrs(IOSTANDARD="LVCMOS33"),
                ),
            )
        ]

    if platform is None:
        exit()

    platform.add_resources(additional_resources)
    fragment = Fragment.get(top, platform)
    platform.build(
        fragment,
        build_dir="build/{}".format(platform_name),
        run_script=False,
        do_program=False,
        script_after_read="add_files ../../../vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci",
    )
