import array
import datetime as dt
import random
import sys

from nmigen import *
from nmigen.build import *
from nmigen_boards.arty_a7 import ArtyA7Platform

from src.rtl.kitchensink import *
from src.rtl.riscv import *

__all__ = ["main"]


class Top(Elaboratable):
    def elaborate(self, platform):
        domain = "hart"

        m = Module()
        m.submodules.pll = pll = PLL(mult=16, div=1, domains={domain: 128})
        m.submodules.hart = hart = Hart(domain=domain)
        m.submodules.uart = uart = UART(
            domain,
            4
            if isinstance(platform, SimPlatform)
            else round(
                pll.get_frequency_ratio(domain)
                * platform.default_clk_frequency
                / 115200
            ),
        )

        with open("build/firmware.bin", mode="rb") as f:
            firmware = array.array("I")
            assert firmware.itemsize == 4
            file_size = os.stat(f.name).st_size
            assert file_size % 4 == 0
            firmware.fromfile(f, file_size // 4)

        comb = m.d.comb
        sync = m.d[domain]

        rom = Memory(width=32, depth=32)  # file_size // 4, init=firmware)
        m.submodules.irom_rp = irom_rp = rom.read_port(domain="comb")
        m.submodules.drom_rp = drom_rp = rom.read_port(domain="comb")

        ram = Memory(width=32, depth=file_size // 4, init=firmware)
        m.submodules.iram_rp = iram_rp = ram.read_port(domain="comb")
        m.submodules.dram_rp = dram_rp = ram.read_port(domain="comb")
        m.submodules.dram_wp = dram_wp = ram.write_port(domain=domain, granularity=8)

        m.submodules.sdram = sdram = SDRAM()

        if not isinstance(platform, SimPlatform):
            comb += [
                platform.request("led", 0).eq(hart.halt),
                platform.request("led", 1).eq(sdram.app_rdy),
                platform.request("uart").tx.eq(uart.tx_o),
            ]

        # MEMORY
        dmem_addr = hart.dmem_addr
        imem_addr = hart.imem_addr

        # IMEM
        with m.If(imem_addr[28:32] == 2):
            # ROM
            comb += [
                irom_rp.addr.eq(imem_addr[2:28]),
                hart.imem_data.eq(irom_rp.data),
            ]
        with m.Else():
            # RAM
            comb += [
                hart.imem_data.eq(iram_rp.data),
                iram_rp.addr.eq(imem_addr[2:28]),
            ]

        # DMEM
        with m.If(dmem_addr == 0x1000_0000):
            # UART
            with m.If(hart.dmem_wmask.any()):
                comb += [
                    uart.tx_rdy.eq(1),
                    uart.tx_data.eq(hart.dmem_wdata),
                ]
            with m.Else():
                comb += [
                    hart.dmem_rdata.eq(uart.tx_ack),
                ]
        with m.Elif(dmem_addr == 0x1000_0004):
            # SDRAM
            with m.If(hart.dmem_rmask.any()):
                comb += hart.dmem_rdata.eq(
                    Cat(
                        sdram.pll_locked,
                        sdram.mig_init_calib_complete,
                        sdram.app_rdy,
                        sdram.app_wdf_rdy,
                    )
                )
        with m.Elif(dmem_addr[28:32] == 2):
            # ROM
            comb += [
                # read
                drom_rp.addr.eq(dmem_addr[2:28]),
                hart.dmem_rdata.eq(drom_rp.data),
            ]
        with m.Else():
            # RAM
            comb += [
                # read
                dram_rp.addr.eq(dmem_addr[2:28]),
                hart.dmem_rdata.eq(dram_rp.data),
                # write
                dram_wp.en.eq(hart.dmem_wmask),
                dram_wp.addr.eq(dmem_addr[2:28]),
                dram_wp.data.eq(hart.dmem_wdata),
            ]

        if isinstance(platform, SimPlatform):

            def process():
                print("~" * 148)
                needs_lf = False
                while True:
                    yield Settle()
                    dmem_addr = yield hart.dmem_addr
                    dmem_rmask = yield hart.dmem_rmask
                    dmem_rdata = yield hart.dmem_rdata
                    dmem_wmask = yield hart.dmem_wmask
                    dmem_wdata = yield hart.dmem_wdata
                    # if dmem_rmask != 0:
                    #     print(
                    #         f"Reading {dmem_addr:#010x} rmask {dmem_rmask:#06b}: {dmem_rdata:#010x}"
                    #     )
                    # if dmem_wmask != 0:
                    #     print(
                    #         f"Writing {dmem_addr:#010x} wmask {dmem_wmask:#06b}: {dmem_wdata:#010x}"
                    #     )
                    if dmem_addr == 0x1000_0000:
                        if dmem_rmask != 0:
                            yield hart.dmem_rdata.eq(1)
                        if dmem_wmask != 0:
                            char = chr(dmem_wdata & 0xFF)
                            print(char, end="")
                            needs_lf = char != "\n"

                    # yield hart.imem_stall.eq(random.randrange(100)<90)
                    yield Tick(domain)
                    trap = yield hart.trap
                    if trap:
                        mcause = yield hart.mcause

                        if needs_lf:
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
                        break

            platform.add_sync_process(process, domain=domain)

        return m


def main():
    platform_name = sys.argv[1] if len(sys.argv) > 1 else None

    if platform_name == "formal":
        platform = FormalPlatform()
        additional_resources = []

    elif platform_name == "sim":
        platform = SimPlatform(100e6)
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
    else:
        print("Unknown platform")
        exit()

    platform.add_resources(additional_resources)

    mig_dir = ""
    build_dir = f"build/{platform_name}"
    fragment = Fragment.get(Top(), platform)
    plan = platform.build(
        fragment,
        build_dir=build_dir,
        do_build=False,
        script_after_read="""
add_files /home/slan/src/HelloArty/build/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci

# add_files platform/formal/testbench.v
# set_property used_in_synthesis false [get_files  platform/formal/testbench.v]
# set_property used_in_implementation false [get_files platform/formal/testbench.v]
# update_compile_order -fileset sources_1
        """,
    )
    if plan is not None:
        plan.execute_local(build_dir, run_script=True)


if __name__ == "__main__":
    main()
