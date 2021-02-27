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

with_sdram = False

class Top(Elaboratable):
    def elaborate(self, platform):
        domain = "hart"

        m = Module()
        m.submodules.pll = pll = PLL(mult=8, div=1, domains={domain: 128})
        m.submodules.hart = hart = Hart(domain=domain)

        with open("build/firmware.bin", mode="rb") as f:
            firmware = array.array("I")
            assert firmware.itemsize == 4
            file_size = os.stat(f.name).st_size
            assert file_size % 4 == 0
            firmware.fromfile(f, file_size // 4)

        comb = m.d.comb
        sync = m.d[domain]

        ram = Memory(width=32, depth=file_size // 4, init=firmware)
        m.submodules.iram_rp = iram_rp = ram.read_port(domain="comb")
        m.submodules.dram_rp = dram_rp = ram.read_port(domain="comb")
        m.submodules.dram_wp = dram_wp = ram.write_port(domain=domain, granularity=8)

        m.submodules.immu = immu = MMU()
        comb += hart.ibus.connect(immu.bus)

        ram_ibus = Record(bus_layout)
        immu.add_device(ram_ibus, 0x0000_0000, 0x1000_0000)
        comb += [
            ram_ibus.rdy.eq(1),
            ram_ibus.rdata.eq(iram_rp.data),
            iram_rp.addr.eq(ram_ibus.addr[2:28]),
        ]

        m.submodules.dmmu = dmmu = MMU()
        comb += hart.dbus.connect(dmmu.bus)

        ram_dbus = Record(bus_layout)
        dmmu.add_device(ram_dbus, 0x0000_0000, 0x1000_0000)
        comb += [
            ram_dbus.rdy.eq(1),
            dram_rp.addr.eq(ram_dbus.addr[2:28]),
            ram_dbus.rdata.eq(dram_rp.data),
            dram_wp.addr.eq(ram_dbus.addr[2:28]),
            dram_wp.en.eq(ram_dbus.wmask),
            dram_wp.data.eq(ram_dbus.wdata),
        ]

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
        uart_bus = Record(bus_layout)
        dmmu.add_device(uart_bus, 0x1000_0000, 0x1000_0004)
        comb += [
            uart_bus.rdy.eq(1),
            uart_bus.rdata.eq(uart.tx_ack),
            uart.tx_rdy.eq(uart_bus.wmask.any()),
            uart.tx_data.eq(uart_bus.wdata),
        ]

        if isinstance(platform, ArtyA7Platform):
            comb += [
                platform.request("uart").tx.eq(uart.tx_o),
            ]

        if with_sdram:
            m.submodules.sdram = sdram = SDRAM(domain=domain)
            sdram_bus = Record(bus_layout)
            dmmu.add_device(sdram_bus, 0x1000_0004, 0x1000_0008)
            comb += [
                sdram_bus.rdata.eq(
                    Cat(
                        sdram.output.pll_locked,
                        sdram.output.mig_init_calib_complete,
                        sdram.output.app_rdy,
                    )
                ),
            ]

        if isinstance(platform, SimPlatform):

            def process():
                print("~" * 148)
                needs_lf = False
                while True:
                    yield Settle()
                    dmem_addr = yield hart.dbus.addr
                    dmem_rdata = yield hart.dbus.rdata
                    dmem_wmask = yield hart.dbus.wmask
                    dmem_wdata = yield hart.dbus.wdata
                    # if dmem_wmask != 0:
                    #     print(
                    #         f"Writing {dmem_addr:#010x}: {dmem_wdata:#010x} (wmask {dmem_wmask:#06b})"
                    #     )
                    # else:
                    #     print(
                    #         f"Reading {dmem_addr:#010x}: {dmem_rdata:#010x}"
                    #     )
                    uart_tx_rdy = yield uart.tx_rdy
                    if uart_tx_rdy:
                        uart_tx_data = yield uart.tx_data
                        char = chr(uart_tx_data & 0xFF)
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
        script_after_read=""
        if not with_sdram
        else "add_files /home/slan/src/HelloArty/build/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci",
    )
    if plan is not None:
        plan.execute_local(build_dir, run_script=True)


if __name__ == "__main__":
    main()
