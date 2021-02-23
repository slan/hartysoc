import datetime as dt
import array, sys, random

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
        m.submodules.pll = pll = PLL(mult=16, div=1, domains={domain: 48})
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

        if not isinstance(platform, SimPlatform):
            comb += [
                platform.request("led", 0).eq(hart.halt),
                platform.request("led", 1).eq(uart.tx_o),
                platform.request("uart").tx.eq(uart.tx_o),
            ]
            mem = Memory(width=32, depth=file_size // 4, init=firmware)
            m.submodules.imem_rp = imem_rp = mem.read_port(domain="comb")
            m.submodules.dmem_rp = dmem_rp = mem.read_port(domain="comb")
            m.submodules.dmem_wp = dmem_wp = mem.write_port(
                domain=domain, granularity=8
            )

            # MEMORY
            dmem_addr = hart.dmem_addr

            # FETCH
            comb += [
                hart.imem_data.eq(imem_rp.data),
                imem_rp.addr.eq(hart.imem_addr[2:20]),
            ]

            with m.If(dmem_addr[20:32].any()):
                # I/O
                with m.If(hart.dmem_wdata.any()):
                    comb += [
                        uart.tx_rdy.eq(1),
                        uart.tx_data.eq(hart.dmem_wdata),
                    ]
                with m.Else():
                    comb += [
                        hart.dmem_rdata.eq(uart.tx_ack),
                    ]
            with m.Else():
                # DATA
                comb += [
                    # read
                    dmem_rp.addr.eq(dmem_addr[2:20]),
                    hart.dmem_rdata.eq(dmem_rp.data),
                    # write
                    dmem_wp.en.eq(hart.dmem_wmask),
                    dmem_wp.addr.eq(dmem_addr[2:20]),
                    dmem_wp.data.eq(hart.dmem_wdata),
                ]
        else:

            def process():
                print("~" * 148)
                needs_lf = False
                while True:
                    yield Settle()
                    imem_addr = yield hart.imem_addr
                    yield hart.imem_data.eq(firmware[imem_addr >> 2])
                    yield Settle()
                    dmem_addr = yield hart.dmem_addr
                    dmem_wmask = yield hart.dmem_wmask
                    if dmem_wmask == 0:
                        if dmem_addr >= 0x1000_0000:
                            yield hart.dmem_rdata.eq(1)
                        else:
                            yield hart.dmem_rdata.eq(firmware[dmem_addr >> 2])
                        yield Settle()
                    else:
                        dmem_wdata = yield hart.dmem_wdata
                        if dmem_addr >= 0x1000_0000:
                            char = chr(dmem_wdata & 0xFF)
                            print(char, end="")
                            needs_lf = char != "\n"
                        else:
                            if dmem_wmask == 0xF:
                                firmware[dmem_addr >> 2] = dmem_wdata
                            elif dmem_wmask == 0x1:
                                firmware[dmem_addr >> 2] = dmem_wdata & 0x000000FF
                            elif dmem_wmask == 0x2:
                                firmware[dmem_addr >> 2] = dmem_wdata & 0x0000FF00
                            elif dmem_wmask == 0x4:
                                firmware[dmem_addr >> 2] = dmem_wdata & 0x00FF0000
                            elif dmem_wmask == 0x8:
                                firmware[dmem_addr >> 2] = dmem_wdata & 0xFF000000
                            else:
                                print("Not implemented", hex(dmem_wmask))
                                break

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

    if platform is None:
        exit()

    platform.add_resources(additional_resources)
    fragment = Fragment.get(Top(), platform)
    platform.build(
        fragment,
        build_dir=f"build/{platform_name}",
        run_script=True,
        do_program=False,
        # script_after_synth="""
        # set_property CONFIG_VOLTAGE 3.3 [current_design]
        # set_property CFGBVS VCCO [current_design]
        # """,
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
