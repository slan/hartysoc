from nmigen import *

from .counter import *
from .pll import *


class MultiBlinky(Elaboratable):
    def elaborate(self, platform):
        m = Module()

        domain_defs=[("cd1",8),("cd2",4),("cd3",2)]

        m.submodules.pll = PLL(mult=8,domain_defs=domain_defs)

        cycles = int(platform.default_clk_frequency) - 1

        for i, (domain_name,_) in enumerate(domain_defs):
            if domain_name is not None:
                counter = Counter(cycles, domain_name)
                m.submodules[f"counter_{domain_name}"] = counter
                m.d.comb += platform.request("led", i).eq(counter.out)

        return m
