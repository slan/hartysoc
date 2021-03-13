# Notes - Hart

## Memory access

In each cycle the hart needs:
- 1 read (fetch)

or
- 2 reads (fetch + load)

or 
- 1 read and 1 write (fetch + store)

## Single-cycle operation

Using a dual port distributed RAM (2 asynchronous reads, 1 synchronous write) to get CPI=1
- `ibus` connected to read port
- `dbus` connected to read-write port

### IF
- `pc` is connected to `ibus.addr`

> [hart.py](../hdl/riscv/hart.py) is combinatorial. `pc` is the register breaking the loop and "stepping" the CPU.

The following steps are gated by `ibus.rdy`

### ID
- `pc` is connected to the decoder
- `ibus.rdata` is connected to the decoder

> [decoder.py](../hdl/riscv/decoder.py) is combinatorial.

### EX
- register sources are connected
- alu inputs and function are connected

> [registers.py](../hdl/riscv/registers.py) is implemented as distributed RAM (combinatorial).

> [alu.py](../hdl/riscv/alu.py) is combinatorial.

### MEM

Gate: memory access (`decoder.mem:func`)

- `alu.out[2:]` is connected to `dbus.addr`

If LOAD:
- `alu.out[:2]` is used to compute read mask and is connected to `dbus.rmask`

If STORE:
- `alu.out[:2]` is used to compute write mask and is connected to `dbus.wmask`
- part of `registers.rs2_data` is connected to `dbus.wdata`

### WB

Gate: `dbus.rdy` or no memory access(`decoder.mem_func`)

- decoder (`rd_addr`) is connected to register write address (`registers.rd_addr`)

If LOAD:

- `dbus.rdata` is connected to `registers.rd_wdata`

Else:

- One of `alu.out`, `pc`+4, `mcycle`, `minstret` is connected to `registers.rd_wdata` according to `decoder.reg_src`
- `pc` is updated for the next cycle, based on branch condition
