import sys

from nmigen import *
from nmigen.build import *
from nmigen_boards.arty_a7 import ArtyA7Platform
from kitchensink import *

class RAM(Elaboratable):
    pll_locked = Signal()

    def elaborate(self, platform):
        m = Module()

        clks_out = {
            "mig_ref_clk": Signal(),
            "mig_sys_clk": Signal(),
        }

        clk_fb = Signal()

        pll = Instance(
            "PLLE2_BASE",
            p_BANDWIDTH="OPTIMIZED",  # OPTIMIZED, HIGH, LOW
            # Multiply value for all CLKOUT, (2-64)
            p_CLKFBOUT_MULT=10,
            # Phase offset in degrees of CLKFB, (-360.000-360.000).
            p_CLKFBOUT_PHASE=0.0,
            # Input clock period in ns to ps resolution (i.e. 33.333 is 30 MHz).
            p_CLKIN1_PERIOD=10,
            # CLKOUT0_DIVIDE - CLKOUT5_DIVIDE: Divide amount for each CLKOUT (1-128)
            p_CLKOUT0_DIVIDE=5,
            p_CLKOUT1_DIVIDE=3,
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
            o_CLKOUT0=clks_out["mig_ref_clk"],  # 1-bit output: CLKOUT0
            o_CLKOUT1=clks_out["mig_sys_clk"],  # 1-bit output: CLKOUT1
            # Feedback Clocks: 1-bit (each) output: Clock feedback ports
            o_CLKFBOUT=clk_fb,  # 1-bit output: Feedback clock
            o_LOCKED=self.pll_locked,  # 1-bit output: LOCK
            i_CLKIN1=ClockSignal(),  # 1-bit input: Input clock
            # Control Ports: 1-bit (each) input: PLL control ports
            i_PWRDWN=Const(0),  # 1-bit input: Power-down
            i_RST=ResetSignal(),  # 1-bit input: Reset
            # Feedback Clocks: 1-bit (each) input: Clock feedback ports
            i_CLKFBIN=clk_fb,  # 1-bit input: Feedback clock
        )

        m.submodules.pll = pll

        for domain_name in ["mig_ref_clk", "mig_sys_clk"]:
            m.submodules["bufg_{}".format(domain_name)] = Instance(
                "BUFG",
                o_O=ClockSignal(domain_name),  # 1-bit output: Clock output
                i_I=clks_out[domain_name],  # 1-bit input: Clock input
            )

            m.submodules["rss_{}".format(domain_name)] = ResetSynchronizer(
                ~self.pll_locked, domain=domain_name
            )
            m.domains += [ClockDomain(domain_name)]

        return m


if __name__ == "__main__":

    top = SOC()

    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == "sim":

        def process():
            for _ in range(1000):
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
        run_script=True,
        do_program=False,
    )
