from nmigen import *
from nmigen.build import *
from nmigen.lib.cdc import *
from nmigen_boards.arty_a7 import ArtyA7Platform

class PLL(Elaboratable):
    class cd_spec:
        def __init__(self, *, div, local):
            self._div = div
            self._local = local

    def __init__(self, *, mult, div, cd_specs):
        self._cd_specs = cd_specs
        self.mult = mult
        self.div = div
        self.locked = Signal()

    def get_frequency_ratio(self, domain):
        return self.mult / (self.div * self._cd_specs[domain]._div)

    def elaborate(self, platform):

        m = Module()

        for cd_name, cd_spec in self._cd_specs.items():
            m.domains += ClockDomain(cd_name, local=cd_spec._local)
            m.submodules[f"rs_{cd_name}"] = ResetSynchronizer(
                ~self.locked | ResetSignal(), domain=cd_name
            )

        if isinstance(platform, ArtyA7Platform):
            p_clkout_divide = {}
            o_clkout = {}
            for i, (cd_name, cd_spec) in enumerate(self._cd_specs.items()):
                p_clkout_divide[f"p_CLKOUT{i}_DIVIDE"] = cd_spec._div
                # o_clkout[f"o_CLKOUT{i}"] = clk_out
                clk_out = Signal(name=f"pll_clk_{cd_name}")
                o_clkout[f"o_CLKOUT{i}"] = clk_out
                m.submodules[f"pll_bufg_{cd_name}"] = Instance(
                    "BUFG", i_I=clk_out, o_O=ClockSignal(cd_name)
                )

            fb = Signal()
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
                o_CLKFBOUT=fb,  # 1-bit output: Feedback clock
                o_LOCKED=self.locked,  # 1-bit output: LOCK
                i_CLKIN1=ClockSignal(),  # 1-bit input: Input clock
                # Control Ports: 1-bit (each) input: PLL control ports
                i_PWRDWN=Const(0),  # 1-bit input: Power-down
                i_RST=ResetSignal(),  # 1-bit input: Reset
                # Feedback Clocks: 1-bit (each) input: Clock feedback ports
                i_CLKFBIN=fb,  # 1-bit input: Feedback clock
            )
        else:
            m.d.sync += self.locked.eq(1)
            platform.add_resources(
                [
                    Resource(
                        cd_name,
                        0,
                        Pins(cd_name, dir="i"),
                        Clock(
                            platform.default_clk_frequency
                            * self.get_frequency_ratio(cd_name)
                        ),
                    )
                    for cd_name in self._cd_specs.keys()
                ]
            )

        return m
