# hartysoc

A RISC-V SOC implemented in [nmigen](https://github.com/nmigen/nmigen) targeting the [Arty](https://store.digilentinc.com/arty-a7-artix-7-fpga-development-board/) FPGA board.

> Disclaimer: in it's current state, this repo is merely a playground for my learning journey. I am not an expert (read: PR/issues are welcome).

Setup instructions are [here](SETUP.md)

Check `SRCS_FIRMWARE` in the [Makefile](Makefile), default should run an SDRAM test. Use `sim` or `arty`/`prog` targets.

Running on device (code/data in cache, just testing SDRAM R/W):
```
hartysoc 0.2.0 @33.333MHz - Bonjour
-----------------------------------------------
FE 05 01 00 AA AA 55 55 55 55 AA AA 99 99 66 66
BB BB 11 11 EE EE 44 44 44 44 EE EE DD DD 88 88
BB BB 11 11 EE EE 44 44 44 44 EE EE DD DD 88 88
BB BB 11 11 EE EE 44 44 44 44 EE EE DD DD 88 88
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F

Writing uint32_t...
00000000 00000001 00000002 00000003
00000004 00000005 00000006 00000007

Writing uint16_t...
0000 0001 0002 0003 0004 0005 0006 0007
0008 0009 000A 000B 000C 000D 000E 000F

Writing uint8_t...
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F

Reading...
00 00 00 00 01 00 00 00 02 00 00 00 03 00 00 00
04 00 00 00 05 00 00 00 06 00 00 00 07 00 00 00
00 00 01 00 02 00 03 00 04 00 05 00 06 00 07 00
08 00 09 00 0A 00 0B 00 0C 00 0D 00 0E 00 0F 00
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
-----------------------------------------------
cycle=3045943 insn=3043621
cpi=1.0000762944
```

## Features

- single-cycle, runs at 33MHz
- verified with [riscv-formal](https://github.com/SymbioticEDA/riscv-formal)
- serial console (output-only)
- SDRAM

## WIP

- an easy way to plug memory-mapped devices on the buses
- GPU: basic VGA is in with a "racing the beam" 1920x1080@60Hz demo screen if you have a [Pmod VGA](https://store.digilentinc.com/pmod-vga-video-graphics-array/).


## Benchmark

Dhrystone `-O3`:
```
Number_Of_Runs: 100
User_Time: 39131 cycles, 39129 insn
Cycles_Per_Instruction: 1.000
Dhrystones_Per_Second_Per_MHz: 2555
DMIPS_Per_MHz: 1.454
```
Dhrystone `-O3 --no-inline`:
```
Number_Of_Runs: 100
User_Time: 47628 cycles, 47627 insn
Cycles_Per_Instruction: 1.000
Dhrystones_Per_Second_Per_MHz: 2099
DMIPS_Per_MHz: 1.194
```

## References

### Core

- [nmigen](https://github.com/nmigen/nmigen)
- [yosys](https://github.com/YosysHQ/yosys)

### Simulation/Validation

- [gtkwave](http://gtkwave.sourceforge.net/)
- [sifive gcc toolchain](https://github.com/sifive/freedom-tools/releases)
- [symbyosys](https://github.com/YosysHQ/SymbiYosys.git)

### Arty

- [nmigen-boards](https://github.com/nmigen/nmigen-boards)
- [vivado](https://www.xilinx.com/products/design-tools/vivado.html)
- [openocd-xpack](https://github.com/xpack-dev-tools/openocd-xpack)
