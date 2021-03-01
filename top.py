import datetime as dt
import sys
from hdl.riscv.enums import TrapCause

from nmigen import *
from nmigen.build import *
from nmigen.sim.core import Settle
from nmigen_boards.arty_a7 import ArtyA7Platform

from hdl.harty import *
from hdl.riscv import *

import hdl.kitchensink as ks

__all__ = ["main"]

with_sdram = False


class Top(Elaboratable):
    def elaborate(self, platform):
        m = Module()

        domain = "hart"
        m.submodules.pll = pll = ks.PLL(mult=16, div=1, domains={domain: 128})
        hart_freq = pll.get_frequency_ratio(domain) * platform.default_clk_frequency

        m.submodules.hart = hart = Hart(domain=domain)

        comb = m.d.comb

        ibus_devices = []
        dbus_devices = []

        m.submodules.ram = ram = RAM(domain=domain)
        ibus_devices += [(ram.ibus, 0x0000_0000, 0x1000_0000)]
        dbus_devices += [(ram.dbus, 0x0000_0000, 0x1000_0000)]

        m.submodules.uart = uart = UART(domain=domain, freq=hart_freq)
        dbus_devices += [(uart.bus, 0x1000_0000, 0x1000_0004)]

        for bus, start, end in ibus_devices:
            with m.If((hart.ibus.addr >= start) & (hart.ibus.addr < end)):
                comb += [hart.ibus.connect(bus)]
        for bus, start, end in dbus_devices:
            with m.If((hart.dbus.addr >= start) & (hart.dbus.addr < end)):
                comb += [hart.dbus.connect(bus)]

        # if with_sdram:
        #     m.submodules.sdram = sdram = SDRAM(domain=domain)
        #     dbus_devices+=[(sdram.bus, 0x1000_0004, 0x1000_0008)]

        if isinstance(platform, ks.SimPlatform):

            def process():
                print("~" * 148)
                while True:
                    yield
                    halt = yield hart.halt
                    if halt:
                        break
                    
                    trap = yield hart.trap
                    if trap:
                        ram.halt = True
                        uart.halt = True
                        yield Settle()
                        mcause = yield hart.mcause

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

            platform.add_sync_process(process, domain=domain)

        return m


def main():
    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == "formal":
        platform = ks.FormalPlatform()

    elif platform_name == "sim":
        platform = ks.SimPlatform(100e6)
        
    elif platform_name == "arty":
        platform = ArtyA7Platform()
    else:
        print("Unknown platform")
        exit()

    build_dir = f"build/{platform_name}"
    fragment = Fragment.get(Top(), platform)
    plan = platform.build(
        fragment,
        build_dir=build_dir,
        do_build=False,
        script_after_read=""
        if not with_sdram
        else "add_files /home/slan/src/HelloArty/build/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci",
    )
    if plan is not None:
        plan.execute_local(build_dir, run_script=True)


if __name__ == "__main__":
    main()
