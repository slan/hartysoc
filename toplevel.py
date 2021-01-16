from typing import List
from nmigen import Elaboratable, Module, Signal, Mux, Memory
from nmigen.build import Platform
from nmigen.cli import main_parser, main_runner
from nmigen.back.pysim import Simulator, ClockSignal, ResetSignal
from nmigen.asserts import Assert, Cover, Past


class Core(Elaboratable):
    def __init__(self):
        self.pc = Signal(32)
        self.instr = Signal(32)
        self.stage = Signal(3)
        self.mem = Memory(width=32, depth=16, init=[i for i in range(0, 16)])
        self.rom = self.mem.read_port(transparent=False)
        self.ram = self.mem.write_port()

    def elaborate(self, platform: Platform) -> Module:
        m = Module()

        with m.If(self.stage == 0):
            m.d.sync += self.rom.addr.eq(self.pc)
            m.d.sync += self.rom.en.eq(1)
            m.d.sync += self.stage.eq(1)
        with m.If(self.stage == 1):
            m.d.sync += self.instr.eq(self.rom.data)
            m.d.sync += self.stage.eq(2)
        with m.If(self.stage == 2):
            m.d.sync += self.pc.eq(self.pc+1)
            m.d.sync += self.stage.eq(0)

        return m

    def ports(self) -> List[Signal]:
        return [self.pc, self.instr]


if __name__ == "__main__":
    parser = main_parser()
    args = parser.parse_args()

    top = Module()
    core = Core()
    top.submodules.core = core

    # top.d.comb += Assert(clocky.x <= 100)
    # with top.If(~Past(clocky.load)):
    #     with top.If(clocky.x == 0):
    #         pass
    #     with top.Else():
    #         top.d.sync += Assert(clocky.x == (Past(clocky.x)+1))

    # main_runner(parser, args, top, ports=[]+clocky.ports())

    def process():
        yield core.ram.addr.eq(3)
        yield core.ram.data.eq(3)
        yield core.ram.en.eq(1)
        yield core.pc.eq(0x0)
        value = yield core.rom.data
        print(value)
        value = yield core.rom.data
        print(value)
        value = yield core.rom.data
        print(value)
        value = yield core.rom.data
        print(value)
        value = yield core.rom.data
        print(value)
        yield
        yield
        yield
        yield
        yield
        yield
        yield
        yield

    sim = Simulator(top)
    sim.add_clock(1e-6)
    sim.add_sync_process(process)
    with sim.write_vcd('toplevel.vcd', None, traces=[]+core.ports()):
        sim.run()
