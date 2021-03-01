import array
import sys

from nmigen import *

from ..kitchensink import PLL, SimPlatform
from ..riscv import *
from .console import Console
from .ram import RAM
from .sdram import SDRAM


class HartySOC(Elaboratable):
    def __init__(self, *, with_sdram=False):
        self._with_sdram = with_sdram

    def elaborate(self, platform):
        m = Module()

        domain = "hart"
        m.submodules.pll = pll = PLL(mult=16, div=1, domains={domain: 128})
        hart_freq = pll.get_frequency_ratio(domain) * platform.default_clk_frequency

        m.submodules.hart = hart = Hart(domain=domain)

        comb = m.d.comb

        ibus_devices = []
        dbus_devices = []

        m.submodules.ram = ram = RAM(domain=domain)
        ibus_devices += [(ram.ibus, 0x0000_0000, 0x1000_0000)]
        dbus_devices += [(ram.dbus, 0x0000_0000, 0x1000_0000)]

        m.submodules.console = console = Console(domain=domain, domain_freq=hart_freq)
        dbus_devices += [(console.bus, 0x1000_0000, 0x1000_0004)]

        for bus, start, end in ibus_devices:
            with m.If((hart.ibus.addr >= start) & (hart.ibus.addr < end)):
                comb += [hart.ibus.connect(bus)]
        for bus, start, end in dbus_devices:
            with m.If((hart.dbus.addr >= start) & (hart.dbus.addr < end)):
                comb += [hart.dbus.connect(bus)]

        if self._with_sdram:
            m.submodules.sdram = sdram = SDRAM(domain=domain)
            dbus_devices += [(sdram.bus, 0x1000_0004, 0x1000_0008)]

        if isinstance(platform, SimPlatform):

            def process():
                print("~" * 148)
                while True:
                    yield

                    trap = yield hart.trap
                    if trap:
                        mcause = yield hart.mcause

                        if console.last_output != "\n":
                            print()

                        print("~" * 148)
                        print(
                            f"*** TRAP ***\n  mcause: {TrapCause(mcause).name}/{mcause}"
                        )

                        mcycle = yield hart.mcycle
                        minstret = yield hart.minstret

                        cpi = mcycle / minstret if minstret != 0 else "N/A"
                        print(f"  mcycle: {mcycle}\nminstret: {minstret}\n\ncpi={cpi}")
                        print("-" * 148)
                        pc = yield hart.decoder.pc
                        insn = yield hart.decoder.insn
                        print(f" pc: {pc:#010x}   insn: {insn:#010x}")
                        for i in range(0, 32):
                            x = yield hart.registers._rp1.memory._array[i]
                            if i < 10:
                                sys.stdout.write(" ")
                            sys.stdout.write(f"x{i}: {x:#010x}    ")
                            if i % 8 == 7:
                                print()

                    halt = yield hart.halt
                    if halt:
                        ram.halt = True
                        console.halt = True
                        break

            platform.add_sync_process(process, domain=domain)

        return m
