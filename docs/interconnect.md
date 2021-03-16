# Notes - Interconnect

The bus has memory-mapped devices, the role of the interconnect is to direct reads and writes to a specific device, based on the upper 4 bits of the address. I'm using the following memory map:

 top bits | device  | type | read              | write
----------|---------|------|-------------------|---
 `0001`   | Console | I/O  | uart readiness    | send byte to UART
 `0002`   | SOCInfo | ROM  | hw info (freq...) | N/A
 `0007`   | RAM     | RAM  | value at `addr`   | stores `wdata` at address `addr` according to (byte) mask `wmask`


## Use cases

- ibus not ready -> FETCH LOOP
- ibus and dbus to different devices
  - dbus not ready -> NON-CACHED LOOP
  - dbus ready -> EXECUTE
- ibus and dbus to same devices -> CACHED LOOP

## Implementation

![Diagram](Interconnect.svg)
