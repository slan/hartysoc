# HelloAr

## Setup

### Simulation

- nmigen
- gtkwave
- yosys
- sifive gcc toolchain

### Arty

- Vivado
- [Adept runtime v2.21.2](https://mautic.digilentinc.com/adept-runtime-download)
- [Adept utilities v2.4.1](https://mautic.digilentinc.com/adept-utilities-download)
- openocd

## Benchmark

Single cycle: timing valid @33MHz with dhrystone:
```
Number_Of_Runs: 100
User_Time: 39022 cycles, 39022 insn
Cycles_Per_Instruction: 1.000
Dhrystones_Per_Second_Per_MHz: 2562
DMIPS_Per_MHz: 1.458
```
