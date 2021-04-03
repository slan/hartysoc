# Notes - MIG

Recommendations from the [reference manual](https://reference.digilentinc.com/reference/programmable-logic/arty-a7/reference-manual):

- data width:  16 bits
- input clock: 166.667MHz

Full details from [this](https://forum.digilentinc.com/topic/18555-arty-a7-and-mig) forum thread

- Clock 3000ps (333MHz)
- PHY/Controller 4:1
- Part MT41K128M16XX-15E
- Voltage 1.35
- Data width 16
- Data mask checked
- Bank machines 4
- Ordering Normal (?)
- Input clock 6000ps (167MHz)
- Output impedance RZQ/6
- RTT RZQ/6
- Chip select checked
- System clock no buffer
- Ref clock no buffer
- Reset polarity Active LOW
- Internal Vref checked
- IO Power reduction ON
- XADC Instantiation Enabled
- Internal termination impedance 50 Ohms

