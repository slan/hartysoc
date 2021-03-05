from hdl.kitchensink.simplatform import SimPlatform
import sys

from nmigen import *
from nmigen.lib.fifo import AsyncFIFO
from nmigen.build import *
from nmigen.sim.core import Settle
from nmigen_boards.arty_a7 import ArtyA7Platform

import hdl.kitchensink as ks
from hdl.harty import *
from hdl.riscv import *


class MIGTester(Elaboratable):
    def elaborate(self, platform):
        m = Module()

        m.submodules.mig = mig = ks.MIG()
        m.submodules.mem = mem_wp = Memory(width=128, depth=16).write_port(
            domain=mig.ui_domain
        )

        comb = m.d.comb
        sync = m.d[mig.ui_domain]

        addr = Signal(28)

        with m.FSM(domain=mig.ui_domain):

            with m.State("DO_READ"):
                with m.If(mig.app_rdy):
                    comb += [
                        mig.app_en.eq(1),
                        mig.app_cmd.eq(1),
                        mig.app_addr.eq(addr),
                    ]
                    m.next = "WAIT_DATA"
            with m.State("WAIT_DATA"):
                with m.If(mig.app_rd_data_valid):
                    with m.If(addr < 16):
                        comb += [
                            mem_wp.addr.eq(addr),
                            mem_wp.en.eq(1),
                            mem_wp.data.eq(mig.app_rd_data),
                        ]
                        sync += addr.eq(addr + 1)
                        m.next = "DO_READ"
                    with m.Else():
                        m.next = "END"
            with m.State("END"):
                sync += platform.request("led").eq(1)

        if isinstance(platform, SimPlatform):

            def process():
                yield
                yield
                yield
                yield
                yield

            platform.add_sync_process(process, mig.ui_domain)

        return m


with_sdram = True
# top = HartySOC(with_sdram=with_sdram)
# top = ks.VGA()
top = MIGTester()


def main():
    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == "formal":
        platform = ks.FormalPlatform()

    elif platform_name == "sim":
        platform = ks.SimPlatform(100e6)

    elif platform_name == "arty":
        platform = ArtyA7Platform()
        platform.add_resources(
            [
                Resource(
                    "vgapmod",
                    0,
                    Subsignal(
                        "hsync",
                        Pins("7", dir="o", conn=("pmod", 2)),
                        Attrs(IOSTANDARD="LVCMOS33"),
                    ),
                    Subsignal(
                        "vsync",
                        Pins("8", dir="o", conn=("pmod", 2)),
                        Attrs(IOSTANDARD="LVCMOS33"),
                    ),
                    Subsignal(
                        "r",
                        Pins("1 2 3 4", dir="o", conn=("pmod", 1)),
                        Attrs(IOSTANDARD="LVCMOS33"),
                    ),
                    Subsignal(
                        "g",
                        Pins("1 2 3 4", dir="o", conn=("pmod", 2)),
                        Attrs(IOSTANDARD="LVCMOS33"),
                    ),
                    Subsignal(
                        "b",
                        Pins("7 8 9 10", dir="o", conn=("pmod", 1)),
                        Attrs(IOSTANDARD="LVCMOS33"),
                    ),
                )
            ]
        )
    else:
        print("Unknown platform")
        exit()

    build_dir = f"build/{platform_name}"
    fragment = Fragment.get(top, platform)
    plan = platform.build(
        fragment,
        build_dir=build_dir,
        do_build=False,
        script_after_read=""
        if not with_sdram
        else "add_files ../mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci;quit",
    )
    if plan is not None:
        plan.execute_local(build_dir, run_script=True)


if __name__ == "__main__":
    main()
