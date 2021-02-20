import datetime as dt
import array, sys

from nmigen import *
from nmigen.build import *
from nmigen_boards.arty_a7 import ArtyA7Platform

from src.rtl.riscv import *
from src.rtl.kitchensink import *

__all__ = ["main"]

class Top(Elaboratable):
    def elaborate(self, platform):
        domain = "hart"

        m = Module()
        m.submodules.pll = PLL(mult=16, div=1, domains=[(domain, 20)])
        m.submodules.hart = hart = Hart(domain=domain)
        m.submodules.imem = imem = ROM(1024//4)
        m.submodules.dmem = dmem = RAM(1024//4, domain=domain)

        with open("build/firmware.bin", mode='rb') as f:
            data = array.array("I")
            data.frombytes(f.read())
            imem.set_content(data)

        comb = m.d.comb
        sync = m.d[domain]

        with m.If(hart.trap):
            comb += platform.request("led").eq(1)

        comb += [
            # imem read
            hart.imem_data.eq(imem.data),
            # dmem read
            dmem.addr.eq(hart.dmem_addr),
            hart.dmem_rdata.eq(dmem.rdata),
            # dmem write
            dmem.wmask.eq(hart.dmem_wmask),
            dmem.wdata.eq(hart.dmem_wdata),
        ]

        sync += [
            imem.addr.eq(hart.imem_addr),
        ]

        if isinstance(platform, SimPlatform):

            def process():
                print("~" * 148)
                for _ in range(1000):
                    yield
                    yield Settle()
                    trap = yield hart.trap
                    if trap:
                        mcause = yield hart.mcause
                        if TrapCause(mcause) == TrapCause.M_ECALL:
                            # a7 is syscall
                            # a0 is arg0
                            SBI_EXT_0_1_CONSOLE_PUTCHAR = 0x1
                            a7 = yield hart.registers._rp1.memory._array[17]
                            if a7 == SBI_EXT_0_1_CONSOLE_PUTCHAR:
                                a0 = yield hart.registers._rp1.memory._array[10]
                                print(chr(a0))
                                continue
                                # ret.error = a0;
                                # ret.value = a1;
                        else:
                            print("~" * 148)
                            print(f"*** TRAP - MCAUSE={TrapCause(mcause).name}/{mcause} ***")

                            mcycle = yield hart.mcycle
                            minstret = yield hart.minstret

                            cpi = mcycle / minstret if minstret != 0 else "N/A"
                            print(f"mcycle={mcycle} minstret={minstret} cpi={cpi}")
                            print("-" * 148)
                            pc = yield hart.rvfi.pc_rdata
                            insn = yield hart.rvfi.insn
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
                        break

            platform.add_sync_process(process, domain=domain)

        return m

def main():
    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == "formal":
        platform = FormalPlatform()
        additional_resources = []

    elif platform_name == "sim":
        platform = SimPlatform(200)
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
    fragment = Fragment.get(Top(), platform)
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

if __name__ == "__main__":
    main()
