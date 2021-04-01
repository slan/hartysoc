# hartysoc

A RISC-V SOC implemented in [nmigen](https://github.com/nmigen/nmigen) targeting the [Arty](https://store.digilentinc.com/arty-a7-artix-7-fpga-development-board/) FPGA board.

> Disclaimer: in it's current state, this repo is merely a playground for my learning journey. I am not an expert (read: PR/issues are welcome).

Setup instructions are [here](SETUP.md)

Check `SRCS_FIRMWARE` in the [Makefile](Makefile), default should run an SDRAM test. Use `sim` or `arty`/`prog` targets.

## Features

- single-cycle, runs at 33MHz
- verified with [riscv-formal](https://github.com/SymbioticEDA/riscv-formal)
- serial console (output-only)
- runs from distributed RAM, block RAM, SDRAM

## WIP

- cache
- GPU: basic VGA is in with a "racing the beam" 1920x1080@60Hz demo screen if you have a [Pmod VGA](https://store.digilentinc.com/pmod-vga-video-graphics-array/).

## Notes

- exploring interconnect and limitations about memory ports vs latency: [toysoc](docs/toysoc.md)

## Benchmark

Dhrystone `-O3`:

From distributed RAM:
```
Number_Of_Runs: 100
User_Time: 39131 cycles, 39129 insn
Cycles_Per_Instruction: 1.000
Dhrystones_Per_Second_Per_MHz: 2555
DMIPS_Per_MHz: 1.454
```
From block RAM:
```
Number_Of_Runs: 100
User_Time: 85866 cycles, 36129 insn
Cycles_Per_Instruction: 2.376
Dhrystones_Per_Second_Per_MHz: 1164
DMIPS_Per_MHz: 0.662
```
From SDRAM (hart clocked @6.25MHz):
```
Number_Of_Runs: 100
User_Time: 238795 cycles, 39129 insn
Cycles_Per_Instruction: 6.102
Dhrystones_Per_Second_Per_MHz: 418
DMIPS_Per_MHz: 0.237
```
From SDRAM (hart clocked @33.33MHz):
```
Number_Of_Runs: 100
User_Time: 613987 cycles, 39129 insn
Cycles_Per_Instruction: 15.691
Dhrystones_Per_Second_Per_MHz: 162
DMIPS_Per_MHz: 0.092
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
