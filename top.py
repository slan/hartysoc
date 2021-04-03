import sys

from nmigen import *
from nmigen.build import *
from nmigen_boards.arty_a7 import ArtyA7Platform

import hdl.kitchensink as ks
from hdl.harty.soc import SOC


with_sdram = False
top = SOC(with_sdram=with_sdram)


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
        else "add_files ../mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci",
        #synth_design_opts="-flatten_hierarchy none -keep_equivalent_registers -no_lc",
        #script_after_synth="write_checkpoint -force top.dcp",
    )
    
    if plan is not None:
        plan.execute_local(build_dir, run_script=True)


if __name__ == "__main__":
    main()
