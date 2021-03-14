# Notes - Arbiter

The bus has memory-mapped devices, the role of the arbiter is to direct reads and writes to a specific device, based on the upper 4 bits of the address. I'm using the following memory map:

 top bits | device  | type | read              | write
----------|---------|------|-------------------|---
 `0001`   | Console | I/O  | uart readiness    | send byte to UART
 `0002`   | SOCInfo | ROM  | hw info (freq...) | N/A
 `0007`   | RAM     | RAM  | value at `addr`   | stores bytes selected by `wmask` from `wdata` at `addr`


Combinatorial loop:
`set_property ALLOW_COMBINATORIAL_LOOPS TRUE [get_nets arbiter/icache_data[8]]`