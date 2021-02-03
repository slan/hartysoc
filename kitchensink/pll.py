from nmigen import *
from nmigen.build import *
from nmigen.lib.cdc import *

from .simplatform import SimPlatform


class PLL(Elaboratable):
    def __init__(self, domain_name: str = "sync", *, mult: int, div: int = 1, domain_defs):
        self.domain_name = domain_name
        self.mult = mult
        self.div = div
        self.domain_defs = domain_defs

    def elaborate(self, platform):

        clk_fb = Signal()
        pll_locked = Signal()

        m = Module()

        p_clkout_divide = {}
        o_clkout = {}
        for i, (cd, div) in enumerate(self.domain_defs):
            p_clkout_divide[f"p_CLKOUT{i}_DIVIDE"] = div

            clkout = Signal(name=f"pllout_{cd}")
            o_clkout[f"o_CLKOUT{i}"] = clkout

            m.domains += ClockDomain(cd)
            m.submodules[f"rs_{cd}"] = ResetSynchronizer(
                ~pll_locked, domain=cd
            )
            m.submodules[f"bufg_{cd}"] = Instance(
                "BUFG", i_I=clkout, o_O=ClockSignal(cd)
            )

        m.submodules.pll = Instance(
            "PLLE2_BASE",
            p_BANDWIDTH="OPTIMIZED",  # OPTIMIZED, HIGH, LOW
            # Multiply value for all CLKOUT, (2-64)
            p_CLKFBOUT_MULT=self.mult,
            # Phase offset in degrees of CLKFB, (-360.000-360.000).
            p_CLKFBOUT_PHASE=0.0,
            # Input clock period in ns to ps resolution (i.e. 33.333 is 30 MHz).
            p_CLKIN1_PERIOD=1e9 / platform.default_clk_frequency,
            # CLKOUT0_DIVIDE - CLKOUT5_DIVIDE: Divide amount for each CLKOUT (1-128)
            **p_clkout_divide,
            p_DIVCLK_DIVIDE=self.div,  # Master division value, (1-56)
            # Reference input jitter in UI, (0.000-0.999).
            p_REF_JITTER1=0.0,
            # Delay DONE until PLL Locks, ('TRUE'/'FALSE')
            p_STARTUP_WAIT="TRUE",
            # Clock Outputs: 1-bit (each) output: User configurable clock outputs
            **o_clkout,
            # Feedback Clocks: 1-bit (each) output: Clock feedback ports
            o_CLKFBOUT=clk_fb,  # 1-bit output: Feedback clock
            o_LOCKED=pll_locked,  # 1-bit output: LOCK
            i_CLKIN1=ClockSignal(self.domain_name),  # 1-bit input: Input clock
            # Control Ports: 1-bit (each) input: PLL control ports
            i_PWRDWN=Const(0),  # 1-bit input: Power-down
            i_RST=ResetSignal(self.domain_name),  # 1-bit input: Reset
            # Feedback Clocks: 1-bit (each) input: Clock feedback ports
            i_CLKFBIN=clk_fb,  # 1-bit input: Feedback clock
        )

        if isinstance(platform, SimPlatform):
            m.d.comb += pll_locked.eq(1)
            platform.add_resources(
                [
                    Resource(
                        cd,
                        0,
                        Pins(cd, dir="i"),
                        Clock(self.mult * platform.default_clk_frequency / self.div / div),
                    ) for (cd, div) in self.domain_defs
                ]
            )

        return m
