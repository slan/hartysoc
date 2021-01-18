from nmigen import ClockDomain, ClockSignal, Const, Elaboratable, Instance, Module, ResetSignal, Signal
from nmigen.lib.cdc import ResetSynchronizer


class MMCM(Elaboratable):
    def __init__(self):
        self.clk_pin = Signal()

    def elaborate(self, platform):
        clk_fbin = Signal()
        clk_fbout = Signal()
        bufg = Instance("BUFG",
                        o_O=clk_fbin,  # 1-bit output: Clock output
                        i_I=clk_fbout  # 1-bit input: Clock input
                        )
        locked = Signal()
        mmcm = Instance("MMCME2_BASE",
                        p_BANDWIDTH="OPTIMIZED",  # Jitter programming (OPTIMIZED, HIGH, LOW)
                        p_CLKFBOUT_MULT_F=37.125,  # Multiply value for all CLKOUT (2.000-64.000).
                        p_CLKFBOUT_PHASE=0.0,  # Phase offset in degrees of CLKFB (-360.000-360.000).
                        p_CLKIN1_PERIOD=10.0,  # Input clock period in ns to ps resolution (i.e. 33.333 is 30 MHz).
                        # CLKOUT0_DIVIDE - CLKOUT6_DIVIDE: Divide amount for each CLKOUT (1-128)
                        p_CLKOUT1_DIVIDE=4,
                        p_CLKOUT2_DIVIDE=1,
                        p_CLKOUT3_DIVIDE=1,
                        p_CLKOUT4_DIVIDE=1,
                        p_CLKOUT5_DIVIDE=1,
                        p_CLKOUT6_DIVIDE=1,
                        p_CLKOUT0_DIVIDE_F=6.250,  # Divide amount for CLKOUT0 (1.000-128.000).
                        # CLKOUT0_DUTY_CYCLE - CLKOUT6_DUTY_CYCLE: Duty cycle for each CLKOUT (0.01-0.99).
                        p_CLKOUT0_DUTY_CYCLE=0.5,
                        p_CLKOUT1_DUTY_CYCLE=0.5,
                        p_CLKOUT2_DUTY_CYCLE=0.5,
                        p_CLKOUT3_DUTY_CYCLE=0.5,
                        p_CLKOUT4_DUTY_CYCLE=0.5,
                        p_CLKOUT5_DUTY_CYCLE=0.5,
                        p_CLKOUT6_DUTY_CYCLE=0.5,
                        # CLKOUT0_PHASE - CLKOUT6_PHASE: Phase offset for each CLKOUT (-360.000-360.000).
                        p_CLKOUT0_PHASE=0.0,
                        p_CLKOUT1_PHASE=0.0,
                        p_CLKOUT2_PHASE=0.0,
                        p_CLKOUT3_PHASE=0.0,
                        p_CLKOUT4_PHASE=0.0,
                        p_CLKOUT5_PHASE=0.0,
                        p_CLKOUT6_PHASE=0.0,
                        p_CLKOUT4_CASCADE="FALSE",  # Cascade CLKOUT4 counter with CLKOUT6 (FALSE, TRUE)
                        p_DIVCLK_DIVIDE=4,  # Master division value (1-106)
                        p_REF_JITTER1=0.0,  # Reference input jitter in UI (0.000-0.999).
                        p_STARTUP_WAIT="FALSE",  # Delays DONE until MMCM is locked (FALSE, TRUE)

                        # Clock Outputs: 1-bit (each) output: User configurable clock outputs
                        o_CLKOUT0=ClockSignal("pxl"),  # 1-bit output: CLKOUT0
                        #                        CLKOUT0B=CLKOUT0B,  # 1-bit output: Inverted CLKOUT0
                        #                        CLKOUT1=CLKOUT1,  # 1-bit output: CLKOUT1
                        #                        CLKOUT1B=CLKOUT1B,  # 1-bit output: Inverted CLKOUT1
                        #                        CLKOUT2=CLKOUT2,  # 1-bit output: CLKOUT2
                        #                        CLKOUT2B=CLKOUT2B,  # 1-bit output: Inverted CLKOUT2
                        #                        CLKOUT3=CLKOUT3,  # 1-bit output: CLKOUT3
                        #                        CLKOUT3B=CLKOUT3B,  # 1-bit output: Inverted CLKOUT3
                        #                        CLKOUT4=CLKOUT4,  # 1-bit output: CLKOUT4
                        #                        CLKOUT5=CLKOUT5,  # 1-bit output: CLKOUT5
                        #                        CLKOUT6=CLKOUT6,  # 1-bit output: CLKOUT6
                        # Feedback Clocks: 1-bit (each) output: Clock feedback ports
                        o_CLKFBOUT=clk_fbout,  # 1-bit output: Feedback clock0
                        #                        CLKFBOUTB=CLKFBOUTB,  # 1-bit output: Inverted CLKFBOUT
                        # Status Ports: 1-bit (each) output: MMCM status ports
                        o_LOCKED=locked,  # 1-bit output: LOCK

                        # Clock Inputs: 1-bit (each) input: Clock input
                        i_CLKIN1=self.clk_pin,  # 1-bit input: Clock
                        # Control Ports: 1-bit (each) input: MMCM control ports
                        i_PWRDWN=Const(0),  # 1-bit input: Power-down
                        i_RST=ResetSignal(),  # 1-bit input: Reset
                        # Feedback Clocks: 1-bit (each) input: Clock feedback ports
                        i_CLKFBIN=clk_fbin,  # 1-bit input: Feedback clock
                        )

        m = Module()


        m.submodules.bufg = bufg
        m.submodules.mmcm = mmcm
        m.submodules.rs = ResetSynchronizer(~locked, domain='pxl')

        clk = platform.request(platform.default_clk, dir='-')

        m.domains.sync = ClockDomain()
        m.d.comb += ClockSignal().eq(clk)

        m.domains.pxl = ClockDomain()
        m.d.comb += self.clk_pin.eq(clk)

        return m
