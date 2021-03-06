# hartysoc

A RISC-V SOC implemented in [nmigen](https://github.com/nmigen/nmigen) targeting the [Arty](https://store.digilentinc.com/arty-a7-artix-7-fpga-development-board/) FPGA board.

> Disclaimer: in it's current state, this repo is merely a playground for my learning journey. I am not an expert (read: PR/issues are welcome).

Setup instructions are [here](SETUP.md)

Check `SRCS_FIRMWARE` in the [Makefile](Makefile), default should run Dhrystone. There's also a simple [main.c](firmware/main.c) to hack around...

```
make sim
```

## Features

- single-cycle, runs at 33MHz
- verified with [riscv-formal](https://github.com/SymbioticEDA/riscv-formal)
- serial console (output-only)
- SDRAM

## WIP

- an easy way to plug memory-mapped devices on the buses
- SDRAM: automatic controller creation from Xilinx MIG is done, basic test shows calibration success and app ready (with occasional refresh downtime as expected). The core has support for ibus/dbus stalls... in theory.
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
