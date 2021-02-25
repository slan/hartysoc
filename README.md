# Harty

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

Single cycle: timing valid at 33MHz

Dhrystone:
```
Number_Of_Runs: 100
User_Time: 39022 cycles, 39022 insn
Cycles_Per_Instruction: 1.000
Dhrystones_Per_Second_Per_MHz: 2562
DMIPS_Per_MHz: 1.458
```
