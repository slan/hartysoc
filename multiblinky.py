from nmigen import Elaboratable, Module

from counter import Counter
from pll import PLL


class MultiBlinky(Elaboratable):
    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        m.submodules.pll = PLL()
        cycles = int(platform.default_clk_frequency) - 1

        domain_names = ["sync", "cd1", "cd2", "cd4"]
        for i, domain_name in enumerate(domain_names):
            if domain_name is not None:
                counter = Counter(cycles, domain_name)
                m.submodules["counter_{}".format(domain_name)] = counter
                m.d.comb += platform.request("led", i).eq(counter.out)

        return m
