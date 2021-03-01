# Harty

A RISC-V SOC implemented in nmigen targeting the Arty FPGA board.

- verified with [riscv-formal](https://github.com/nmigen/nmigen)
- single-cycle
- UART

## Memory map

Start|End|Type
---|---|---
`0x00000000` | `0x0fffffff` | RAM (256 MB)
`0x10000000` | `0x1fffffff` | I/O
`0x20000000` | `0x2fffffff` | ROM

## Setup

- nmigen
- yosys

### Simulation/Validation

- gtkwave
- sifive gcc toolchain
- symbyosys

### Arty

- nmigen-boards
- vivado
- openocd

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
