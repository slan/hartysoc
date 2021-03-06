from array import array
from os import stat
from sys import stdout

from nmigen import *
from nmigen.sim.core import Passive

from ..kitchensink import PLL, SimPlatform
from ..riscv import *
from .console import Console
from .ram import RAM
from .sdram import SDRAM
from .soc_info import SOCInfo


class SOC(Elaboratable):
    def __init__(self, *, with_sdram=False):
        self._with_sdram = with_sdram

    def elaborate(self, platform):
        m = Module()

        hart_domain = "hart"
        m.submodules.pll = pll = PLL(
            mult=16, div=1, cd_specs={hart_domain: PLL.cd_spec(div=48, local=False)}
        )
        hart_freq = (
            pll.get_frequency_ratio(hart_domain) * platform.default_clk_frequency
        )

        m.submodules.hart = hart = Hart(domain=hart_domain)

        comb = m.d.comb

        ibus_devices = []
        dbus_devices = []

        with open("build/firmware.bin", mode="rb") as f:
            firmware = array("I")
            assert firmware.itemsize == 4
            file_size = stat(f.name).st_size
            assert file_size % 4 == 0
            firmware.fromfile(f, file_size // 4)

        m.submodules.ram = ram = RAM(domain=hart_domain, init=firmware)
        ibus_devices += [(ram.ibus, 0x0000_0000, 0x1000_0000)]
        dbus_devices += [(ram.dbus, 0x0000_0000, 0x1000_0000)]

        m.submodules.console = console = Console(
            domain=hart_domain, domain_freq=hart_freq
        )
        dbus_devices += [(console.bus, 0x1000_0000, 0x1000_0004)]

        m.submodules.soc_info = soc_info = SOCInfo(version="0.2.0", freq=hart_freq)
        dbus_devices += [(soc_info.bus, 0x1000_0100, 0x1000_0200)]

        if self._with_sdram:
            m.submodules.sdram = sdram = SDRAM(domain=hart_domain)
            dbus_devices += [(sdram.bus, 0x2000_0000, 0x4000_0000)]

        for bus, start, end in ibus_devices:
            with m.If((hart.ibus.addr >= start) & (hart.ibus.addr < end)):
                comb += [hart.ibus.connect(bus)]
        for bus, start, end in dbus_devices:
            with m.If((hart.dbus.addr >= start) & (hart.dbus.addr < end)):
                comb += [hart.dbus.connect(bus)]

        if isinstance(platform, SimPlatform):

            def trap_process():
                yield Passive()
                print("~" * 148)
                while True:
                    yield

                    trap = yield hart.trap
                    if trap:
                        mcause = yield hart.mcause

                        if console.last_output != "\n":
                            print()

                        print("~" * 148)
                        mcycle = yield hart.mcycle
                        minstret = yield hart.minstret
                        print(
                            f"*** TRAP *** mcause={TrapCause(mcause).name}/{mcause} mcycle={mcycle} minstret={minstret}"
                        )

                        pc = yield hart.decoder.pc
                        insn = yield hart.decoder.insn
                        print(f" pc: {pc:#010x}   insn: {insn:#010x}")
                        for i in range(0, 32):
                            x = yield hart.registers._rp1.memory._array[i]
                            if i < 10:
                                stdout.write(" ")
                            stdout.write(f"x{i}: {x:#010x}    ")
                            if i % 8 == 7:
                                print()

            platform.add_sync_process(trap_process, domain=hart_domain)

            def watchdog_process():
                while True:
                    yield
                    halt = yield hart.halt
                    if halt:
                        break
                print("=" * 148)
                mcycle = yield hart.mcycle
                minstret = yield hart.minstret
                cpi = mcycle / minstret if minstret != 0 else "N/A"
                print(
                    f"*** HALT *** mcycle={mcycle} minstret={minstret} (cpi: {cpi})"
                )

            platform.add_sync_process(watchdog_process, domain=hart_domain)

        return m
