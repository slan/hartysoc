# HelloArty

LiteX-based blinky on Arty A7-35, following [lab-001](https://github.com/litex-hub/fpga_101/tree/master/lab001).

## Setup

- Vivado
- [Adept runtime v2.21.2](https://mautic.digilentinc.com/adept-runtime-download)
- [Adept utilities v2.4.1](https://mautic.digilentinc.com/adept-utilities-download)

## Utilization

- With comparisons:

|  Ref Name  | Used | Functional Category |
|------------|-----:|---------------------|
| FDRE       |   23 |        Flop & Latch |
| LUT6       |   13 |                 LUT |
| LUT4       |    8 |                 LUT |
| LUT5       |    6 |                 LUT |
| LUT2       |    6 |                 LUT |
| OBUF       |    5 |                  IO |
| LUT3       |    5 |                 LUT |
| LUT1       |    3 |                 LUT |
| CARRY4     |    3 |          CarryLogic |
| FDPE       |    2 |        Flop & Latch |
| BUFG       |    2 |               Clock |
| MMCME2_ADV |    1 |               Clock |
| IBUF       |    1 |                  IO |


- Without:
