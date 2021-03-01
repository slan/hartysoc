from nmigen import *
from nmigen.build import *
from nmigen.lib.cdc import ResetSynchronizer
from .simplatform import SimPlatform
from nmigen_boards.arty_a7 import ArtyA7Platform

#    Name        1920x1080p60
#    Standard      SMPTE 274M
#    VIC                   16
#    Short Name         1080p
#    Aspect Ratio        16:9
#
#    Pixel Clock        148.5 MHz
#    TMDS Clock       1,485.0 MHz
#    Pixel Time           6.7 ns ±0.5%
#    Horizontal Freq.  67.500 kHz
#    Line Time           14.8 μs
#    Vertical Freq.    60.000 Hz
#    Frame Time          16.7 ms
#
#    Horizontal Timings
#    Active Pixels       1920
#    Front Porch           88
#    Sync Width            44
#    Back Porch           148
#    Blanking Total       280
#    Total Pixels        2200
#    Sync Polarity        pos
#
#    Vertical Timings
#    Active Lines        1080
#    Front Porch            4
#    Sync Width             5
#    Back Porch            36
#    Blanking Total        45
#    Total Lines         1125
#    Sync Polarity        pos
#
#    Active Pixels  2,073,600
#    Data Rate           3.56 Gbps
#
#    Frame Memory (Kbits)
#     8-bit Memory     16,200
#    12-bit Memory     24,300
#    24-bit Memory     48,600
#    32-bit Memory     64,800


class VGA(Elaboratable):
    def elaborate(self, platform):
        clk_fb = Signal()
        locked = Signal()
        mmcm = Instance(
            "MMCME2_BASE",
            p_BANDWIDTH="OPTIMIZED",  # Jitter programming (OPTIMIZED, HIGH, LOW)
            p_CLKFBOUT_MULT_F=37.125,  # Multiply value for all CLKOUT (2.000-64.000).
            p_CLKFBOUT_PHASE=0.0,  # Phase offset in degrees of CLKFB (-360.000-360.000).
            p_CLKIN1_PERIOD=10.0,  # Input clock period in ns to ps resolution (i.e. 33.333 is 30 MHz).
            # CLKOUT0_DIVIDE - CLKOUT6_DIVIDE: Divide amount for each CLKOUT (1-128)
            p_CLKOUT1_DIVIDE=4,
            p_CLKOUT0_DIVIDE_F=6.250,  # Divide amount for CLKOUT0 (1.000-128.000).
            # CLKOUT0_DUTY_CYCLE - CLKOUT6_DUTY_CYCLE: Duty cycle for each CLKOUT (0.01-0.99).
            p_CLKOUT0_DUTY_CYCLE=0.5,
            # CLKOUT0_PHASE - CLKOUT6_PHASE: Phase offset for each CLKOUT (-360.000-360.000).
            p_CLKOUT0_PHASE=0.0,
            p_CLKOUT4_CASCADE="FALSE",  # Cascade CLKOUT4 counter with CLKOUT6 (FALSE, TRUE)
            p_DIVCLK_DIVIDE=4,  # Master division value (1-106)
            p_REF_JITTER1=0.0,  # Reference input jitter in UI (0.000-0.999).
            p_STARTUP_WAIT="TRUE",  # Delays DONE until MMCM is locked (FALSE, TRUE)
            # Clock Outputs: 1-bit (each) output: User configurable clock outputs
            o_CLKOUT0=ClockSignal("pxl"),  # 1-bit output: CLKOUT0
            # Feedback Clocks: 1-bit (each) output: Clock feedback ports
            o_CLKFBOUT=clk_fb,  # 1-bit output: Feedback clock0
            # Status Ports: 1-bit (each) output: MMCM status ports
            o_LOCKED=locked,  # 1-bit output: LOCK
            # Clock Inputs: 1-bit (each) input: Clock input
            i_CLKIN1=ClockSignal(),  # 1-bit input: Clock
            # Control Ports: 1-bit (each) input: MMCM control ports
            i_PWRDWN=Const(0),  # 1-bit input: Power-down
            i_RST=ResetSignal(),  # 1-bit input: Reset
            # Feedback Clocks: 1-bit (each) input: Clock feedback ports
            i_CLKFBIN=clk_fb,  # 1-bit input: Feedback clock
        )

        m = Module()

        m.submodules.mmcm = mmcm
        m.submodules.rs = ResetSynchronizer(~locked, domain="pxl")

        # Create pxl clock domain
        m.domains.pxl = ClockDomain("pxl", local=True)

        x_max = 2200 - 1
        y_max = 1125 - 1
        x = Signal(range(x_max))
        y = Signal(range(y_max))

        with m.If(x == x_max):
            m.d.pxl += x.eq(0)
            m.d.pxl += y.eq(Mux(y == y_max, 0, y + 1))
        with m.Else():
            m.d.pxl += x.eq(x + 1)

        vgapmod = platform.request("vgapmod")

        with m.If((y < 1080) & (x < 1920)):
            lfsr = Signal(21, reset=688348)  # xnor taps at 21,19
            m.d.pxl += [
                lfsr.eq(Cat((lfsr >> 1)[:20], (lfsr[0] == lfsr[2]))),
            ]
            rnd = lfsr[:4]
            with m.If(x < 640 - 8 + rnd):
                m.d.comb += [vgapmod.r.eq(0), vgapmod.g.eq(0), vgapmod.b.eq(rnd)]
            with m.Elif(x < 640 + 640 - 8 + rnd):
                m.d.comb += [
                    vgapmod.r.eq(rnd),
                    vgapmod.g.eq(rnd),
                    vgapmod.b.eq(rnd),
                ]
            with m.Elif(x < 640 + 640 + 640):
                m.d.comb += [vgapmod.r.eq(rnd), vgapmod.g.eq(0), vgapmod.b.eq(0)]

        m.d.pxl += [
            vgapmod.hsync.eq((x >= 1920 + 88) & (x < 1920 + 88 + 44)),
            vgapmod.vsync.eq((y >= 1080 + 4) & (y < 1080 + 4 + 5)),
        ]

        return m
