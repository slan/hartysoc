from nmigen import *

from .counter import *
from .pll import *


class MultiBlinky(Elaboratable):
    def elaborate(self, platform):
        m = Module()

        domains=[("cd1",8),("cd2",4),("cd3",2)]

        m.submodules.pll = PLL(mult=8,domains=domains)

        cycles = int(platform.default_clk_frequency) - 1

        for i, (domain_name,_) in enumerate(domains):
            if domain_name is not None:
                counter = Counter(cycles, domain_name)
                m.submodules[f"counter_{domain_name}"] = counter
                m.d.comb += platform.request("led", i).eq(counter.out)

        return m
