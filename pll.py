from nmigen import ClockDomain, ClockSignal, Const, Elaboratable, Instance, Module, Signal
from nmigen.build import Platform
from nmigen.lib.cdc import ResetSynchronizer


class PLL(Elaboratable):
    def elaborate(self, platform: Platform) -> Module:
        clk_fbin = Signal()
        clk_fbout = Signal()
        bufg = Instance('BUFG',
                        o_O=clk_fbin,  # 1-bit output: Clock output
                        i_I=clk_fbout  # 1-bit input: Clock input
                        )
        pll_lock = Signal(reset=1 if platform is None else 0)
        pll = Instance('PLLE2_BASE',
                       p_BANDWIDTH='OPTIMIZED',  # OPTIMIZED, HIGH, LOW
                       # Multiply value for all CLKOUT, (2-64)
                       p_CLKFBOUT_MULT=64,
                       # Phase offset in degrees of CLKFB, (-360.000-360.000).
                       p_CLKFBOUT_PHASE=0.0,
                       # Input clock period in ns to ps resolution (i.e. 33.333 is 30 MHz).
                       p_CLKIN1_PERIOD=10.0,
                       # CLKOUT0_DIVIDE - CLKOUT5_DIVIDE: Divide amount for each CLKOUT (1-128)
                       p_CLKOUT0_DIVIDE=16,
                       p_CLKOUT1_DIVIDE=11,
                       p_CLKOUT2_DIVIDE=1,
                       p_CLKOUT3_DIVIDE=1,
                       p_CLKOUT4_DIVIDE=1,
                       p_CLKOUT5_DIVIDE=1,
                       # CLKOUT0_DUTY_CYCLE - CLKOUT5_DUTY_CYCLE: Duty cycle for each CLKOUT (0.001-0.999).
                       p_CLKOUT0_DUTY_CYCLE=0.5,
                       p_CLKOUT1_DUTY_CYCLE=0.5,
                       p_CLKOUT2_DUTY_CYCLE=0.5,
                       p_CLKOUT3_DUTY_CYCLE=0.5,
                       p_CLKOUT4_DUTY_CYCLE=0.5,
                       p_CLKOUT5_DUTY_CYCLE=0.5,
                       # CLKOUT0_PHASE - CLKOUT5_PHASE: Phase offset for each CLKOUT (-360.000-360.000).
                       p_CLKOUT0_PHASE=0.0,
                       p_CLKOUT1_PHASE=0.0,
                       p_CLKOUT2_PHASE=0.0,
                       p_CLKOUT3_PHASE=0.0,
                       p_CLKOUT4_PHASE=0.0,
                       p_CLKOUT5_PHASE=0.0,
                       p_DIVCLK_DIVIDE=4,  # Master division value, (1-56)
                       # Reference input jitter in UI, (0.000-0.999).
                       p_REF_JITTER1=0.0,
                       # Delay DONE until PLL Locks, ('TRUE'/'FALSE')
                       p_STARTUP_WAIT='TRUE',

                       # Clock Outputs: 1-bit (each) output: User configurable clock outputs
                       o_CLKOUT0=ClockSignal('cd0'),       # 1-bit output: CLKOUT0
                       o_CLKOUT1=ClockSignal('cd1'),  # 1-bit output: CLKOUT1
                       # o_CLKOUT2=ClockSignal('cd2'),  # 1-bit output: CLKOUT2
                       #                       o_CLKOUT3=CLKOUT3,  # 1-bit output: CLKOUT3
                       #                       o_CLKOUT4=CLKOUT4,  # 1-bit output: CLKOUT4
                       #                       o_CLKOUT5=CLKOUT5,  # 1-bit output: CLKOUT5
                       # Feedback Clocks: 1-bit (each) output: Clock feedback ports
                       o_CLKFBOUT=clk_fbout,  # 1-bit output: Feedback clock
                       o_LOCKED=pll_lock,  # 1-bit output: LOCK

                       i_CLKIN1=ClockSignal(),  # 1-bit input: Input clock
                       # Control Ports: 1-bit (each) input: PLL control ports
                       i_PWRDWN=Const(0),  # 1-bit input: Power-down
                       i_RST=Const(0),  # 1-bit input: Reset
                       # Feedback Clocks: 1-bit (each) input: Clock feedback ports
                       i_CLKFBIN=clk_fbin  # 1-bit input: Feedback clock
                       )
        rs = ResetSynchronizer(~pll_lock)

        m = Module()
        m.domains.cd0 = ClockDomain()
        m.submodules.bufg = bufg
        m.submodules.pll = pll
        m.submodules.rs = rs

        # m.d.comb += self.clk_pin.eq(platform.request(platform.default_clk, dir='-'))

        return m
