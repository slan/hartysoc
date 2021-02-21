.section .text
    la a0,data
    lb a1,0(a0)
    lb a2,1(a0)
    lb a3,2(a0)
    lb a4,3(a0)
    lh a5,0(a0)
    lh a6,2(a0)
    lw a7,0(a0)
    call main
.word 0x00000000
data:
    .word 0x12345678