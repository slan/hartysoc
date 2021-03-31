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
from .vga import VGA
from .leds import LEDs
from .interconnect import Interconnect
from .cache import Cache
from .blockram import BlockRAM


class SOC(Elaboratable):
    def __init__(self, *, with_sdram=False):
        self._with_sdram = with_sdram

    def elaborate(self, platform):
        m = Module()

        domain = "hart"
        m.submodules.pll = pll = PLL(
            mult=8,
            div=1,
            cd_specs={domain: PLL.cd_spec(div=128, local=False)},
        )
        hart_freq = pll.get_frequency_ratio(domain) * platform.default_clk_frequency

        m.submodules.hart = hart = Hart(domain=domain, reset_vector=0x8000_0000)

        comb = m.d.comb

        with open("build/firmware.bin", mode="rb") as f:
            firmware = array("I")
            assert firmware.itemsize == 4
            file_size = stat(f.name).st_size
            assert file_size % 4 == 0
            firmware.fromfile(f, file_size // 4)

        m.submodules.ram = ram = RAM(domain=domain, init=firmware)
        m.submodules.console = console = Console(domain=domain, freq=hart_freq)
        # m.submodules.vga = vga = VGA()
        # m.submodules.leds = leds = LEDs(domain=hart_domain)
        m.submodules.soc_info = soc_info = SOCInfo(version="0.2.1", freq=hart_freq)
        if self._with_sdram:
            m.submodules.sdram = sdram = SDRAM(domain=domain)

        m.submodules.i_interconnect = i_interconnect = Interconnect(name="ibus")
        m.submodules.d_interconnect = d_interconnect = Interconnect(name="dbus")

        m.submodules.icache = icache = Cache(domain=domain)

        if self._with_sdram:
            comb += d_interconnect.get_bus(0, "sdram").connect(sdram.bus)

        # comb += interconnect.get_bus(6, "leds").connect(leds.bus)
        # comb += interconnect.get_bus(9, "vga").connect(vga.bus)

        m.submodules.bram = bram = BlockRAM(domain=domain)

        comb += [
            hart.ibus.connect(icache.bus_up),
            icache.bus_down.connect(i_interconnect.bus),
            # i_interconnect.get_bus(0, "bram").connect(bram.bus),
            i_interconnect.get_bus(8, "ram").connect(ram.ibus),
            #
            hart.dbus.connect(d_interconnect.bus),
            # d_interconnect.get_bus(0, "bram").connect(bram.bus),
            d_interconnect.get_bus(1, "console").connect(console.bus),
            d_interconnect.get_bus(2, "soc_info").connect(soc_info.bus),
            d_interconnect.get_bus(8, "ram").connect(ram.dbus),
        ]
        if isinstance(platform, SimPlatform):

            def trap_process():
                yield Passive()
                print("~" * 148)
                while True:
                    yield
                    if (yield hart.trap):

                        if console.last_output != "\n":
                            print()

                        print("~" * 148)
                        mcause = yield hart.mcause
                        print(
                            f"*** TRAP *** mcause={TrapCause(mcause).name}/{mcause}",
                            f"mcycle={(yield hart.mcycle)}",
                            f"minstret={(yield hart.minstret)}",
                        )

                        print(
                            f" pc: {(yield hart.decoder.pc):#010x}  ",
                            f"insn: {(yield hart.decoder.insn):#010x}",
                        )
                        for i in range(0, 32):
                            if i < 10:
                                stdout.write(" ")
                            reg = yield hart.registers._rp1.memory._array[i]
                            stdout.write(f"x{i}: {reg:#010x}    ")
                            if i % 8 == 7:
                                print()

            platform.add_sync_process(trap_process, domain=domain)

            def watchdog_process():
                while True:
                    yield
                    if (yield hart.halt):
                        break
                print("=" * 148)
                mcycle = yield hart.mcycle
                minstret = yield hart.minstret
                cpi = mcycle / minstret if minstret != 0 else "N/A"
                print(f"*** HALT *** mcycle={mcycle} minstret={minstret} (cpi: {cpi})")

            platform.add_sync_process(watchdog_process, domain=domain)

        return m
