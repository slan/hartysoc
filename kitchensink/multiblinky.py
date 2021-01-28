from nmigen import *

from .counter import *
from .pll import *


class MultiBlinky(Elaboratable):
    def elaborate(self, platform):
        m = Module()

        m.submodules.pll = PLL()
        cycles = int(platform.default_clk_frequency) - 1

        domain_names = ["sync", "cd1", "cd2", "cd4"]
        for i, domain_name in enumerate(domain_names):
            if domain_name is not None:
                counter = Counter(cycles, domain_name)
                m.submodules[f"counter_{domain_name}"] = counter
                m.d.comb += platform.request("led", i).eq(counter.out)

        return m
