from nmigen import Elaboratable, Module, Signal


class Counter(Elaboratable):
    def __init__(self, max_value: int, domain_name: str = "sync"):
        self._domain_name = domain_name
        self._max_value = max_value
        self._counter = Signal(range(max_value))
        self.out = Signal()

    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        domain = m.d[self._domain_name]

        with m.If(self._counter == self._max_value):
            domain += self._counter.eq(0)
            domain += self.out.eq(~self.out)
        with m.Else():
            domain += self._counter.eq(self._counter + 1)

        return m
