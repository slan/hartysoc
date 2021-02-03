import sys

from nmigen import *
from nmigen.build import *
from nmigen_boards.arty_a7 import ArtyA7Platform
from kitchensink import *
from riscv import *

import datetime as dt


class Top(Elaboratable):
    def elaborate(self, platform):
        init = [
            0x00000393,
            0x00600313,
            0x006302B3,
            0x005383B3,
            0xFFF30313,
            0xFE031AE3,
            # 0x0000006F,
        ]

        m = Module()
        m.submodules.rom = rom = ROM(init)
        m.submodules.ram = ram = RAM()
        m.submodules.hart = self.hart = Hart(rom, ram)
        m.d.comb += platform.request("led").eq(self.hart.trap)
        return m


if __name__ == "__main__":

    # 	0:		00000393		addi x7 x0 0
    # 	4:		00600313		addi x6 x0 6
    #
    # 00000008 <loop>:
    # 	8:		006302b3		add x5 x6 x6
    # 	c:		005383b3		add x7 x7 x5
    # 	10:		fff30313		addi x6 x6 -1
    # 	14:		fe031ae3		bne x6 x0 -12 <loop>
    # 00000018 <spin>:
    #   18:		0000006f		jal x0 0x0 <spin>

    top = Top()

    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == "formal":
        platform = FormalPlatform()
        additional_resources = []

    elif platform_name == "sim":

        def process():
            print("-" * 148)
            for _ in range(200):
                yield
                trap = yield top.hart.trap
                mcause = yield top.hart.mcause
                if trap:
                    print(f"*** TRAP - MCAUSE={mcause} ***")
                    break
            mcycle = yield top.hart.mcycle
            minstret = yield top.hart.minstret

            time = dt.timedelta(seconds=mcycle / platform.default_clk_frequency)
            print(f"Running time: {time} @{platform.default_clk_frequency}Hz")
            cpi = mcycle / minstret
            print(f"mcycle={mcycle} minstret={minstret} ipc={cpi}")
            print("-" * 148)
            pc = yield top.hart.pc
            instr = yield top.hart.instr
            print(f" pc: {pc:#010x}  instr: {instr:#010x}")
            for i, x in enumerate(top.hart.registers.bank):
                x = yield x
                if i < 10:
                    sys.stdout.write(" ")
                sys.stdout.write(f"x{i}: {x:#010x}    ")
                if i % 8 == 7:
                    print()

        platform = SimPlatform(100)
        platform.add_sync_process(process)
        additional_resources = [
            Resource("led", 0, Pins("led0", dir="o")),
            Resource("led", 1, Pins("led1", dir="o")),
            Resource("led", 2, Pins("led2", dir="o")),
            Resource("led", 3, Pins("led3", dir="o")),
        ]
    elif platform_name == "arty":
        platform = ArtyA7Platform()
        additional_resources = [
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

    if platform is None:
        exit()

    platform.add_resources(additional_resources)
    fragment = Fragment.get(top, platform)
    platform.build(
        fragment,
        build_dir=f"build/{platform_name}",
        run_script=False,
        do_program=False,
        script_after_read="""
#add_files /home/slan/src/HelloArty/build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci

#add_files /home/slan/src/HelloArty/testbench.v
#set_property used_in_synthesis false [get_files  /home/slan/src/HelloArty/testbench.v]
#set_property used_in_implementation false [get_files  /home/slan/src/HelloArty/testbench.v]
#update_compile_order -fileset sources_1
        """,
    )
