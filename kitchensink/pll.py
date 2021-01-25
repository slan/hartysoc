from nmigen import *
from nmigen.build import *
from nmigen.lib.cdc import *

from .simplatform import SimPlatform


class PLL(Elaboratable):
    def __init__(self, domain: str = "sync"):
        self.clk_pin = ClockSignal(domain)
        self.rst_pin = ResetSignal(domain)

    def elaborate(self, platform):

        clk_fb = Signal()
        pll_locked = Signal()

        clks_out = {}
        domain_names = ["cd1", "cd2", "cd4"]
        for domain_name in domain_names:
            clks_out[domain_name] = Signal()

        pll = Instance(
            "PLLE2_BASE",
            p_BANDWIDTH="OPTIMIZED",  # OPTIMIZED, HIGH, LOW
            # Multiply value for all CLKOUT, (2-64)
            p_CLKFBOUT_MULT=8,
            # Phase offset in degrees of CLKFB, (-360.000-360.000).
            p_CLKFBOUT_PHASE=0.0,
            # Input clock period in ns to ps resolution (i.e. 33.333 is 30 MHz).
            p_CLKIN1_PERIOD=1e9 / platform.default_clk_frequency,
            # CLKOUT0_DIVIDE - CLKOUT5_DIVIDE: Divide amount for each CLKOUT (1-128)
            p_CLKOUT1_DIVIDE=8,
            p_CLKOUT2_DIVIDE=4,
            p_CLKOUT4_DIVIDE=2,
            # CLKOUT0_DUTY_CYCLE - CLKOUT5_DUTY_CYCLE: Duty cycle for each CLKOUT (0.001-0.999).
            p_CLKOUT1_DUTY_CYCLE=0.5,
            p_CLKOUT2_DUTY_CYCLE=0.5,
            p_CLKOUT4_DUTY_CYCLE=0.5,
            # CLKOUT0_PHASE - CLKOUT5_PHASE: Phase offset for each CLKOUT (-360.000-360.000).
            p_CLKOUT1_PHASE=0.0,
            p_CLKOUT2_PHASE=0.0,
            p_CLKOUT4_PHASE=0.0,
            p_DIVCLK_DIVIDE=1,  # Master division value, (1-56)
            # Reference input jitter in UI, (0.000-0.999).
            p_REF_JITTER1=0.0,
            # Delay DONE until PLL Locks, ('TRUE'/'FALSE')
            p_STARTUP_WAIT="TRUE",
            # Clock Outputs: 1-bit (each) output: User configurable clock outputs
            o_CLKOUT1=clks_out["cd1"],  # 1-bit output: CLKOUT1
            o_CLKOUT2=clks_out["cd2"],  # 1-bit output: CLKOUT2
            o_CLKOUT4=clks_out["cd4"],  # 1-bit output: CLKOUT4
            # Feedback Clocks: 1-bit (each) output: Clock feedback ports
            o_CLKFBOUT=clk_fb,  # 1-bit output: Feedback clock
            o_LOCKED=pll_locked,  # 1-bit output: LOCK
            i_CLKIN1=self.clk_pin,  # 1-bit input: Input clock
            # Control Ports: 1-bit (each) input: PLL control ports
            i_PWRDWN=Const(0),  # 1-bit input: Power-down
            i_RST=self.rst_pin,  # 1-bit input: Reset
            # Feedback Clocks: 1-bit (each) input: Clock feedback ports
            i_CLKFBIN=clk_fb,  # 1-bit input: Feedback clock
        )

        m = Module()

        for domain_name in domain_names:
            m.domains += ClockDomain(domain_name)
            m.submodules["rss_{}".format(domain_name)] = ResetSynchronizer(
                ~pll_locked, domain=domain_name
            )
            m.submodules["bufg_{}".format(domain_name)] = Instance(
                "BUFG", i_I=clks_out[domain_name], o_O=ClockSignal(domain_name)
            )

        m.submodules.pll = pll

        if isinstance(platform, SimPlatform):
            m.d.comb += pll_locked.eq(1)
            platform.add_resources(
                [
                    Resource(
                        "cd1",
                        0,
                        Pins("cd1", dir="i"),
                        Clock(1 * platform.default_clk_frequency),
                    ),
                    Resource(
                        "cd2",
                        0,
                        Pins("cd2", dir="i"),
                        Clock(2 * platform.default_clk_frequency),
                    ),
                    Resource(
                        "cd4",
                        0,
                        Pins("cd4", dir="i"),
                        Clock(4 * platform.default_clk_frequency),
                    ),
                ]
            )

        return m
