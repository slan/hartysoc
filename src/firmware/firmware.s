    .global main

main:
    addi x6, x0, 6
loop:
    add x5, x6, x6
    add x7, x7, x5
    addi x6, x6, -1
    bne x6, x0, loop

    li a7,1
    li a0,'B'
    ecall
    li a0,'o'
    ecall
    li a0,'n'
    ecall
    li a0,'j'
    ecall
    li a0,'o'
    ecall
    li a0,'u'
    ecall
    li a0,'r'
    ecall
    li a0,' '
    ecall
    li a0,'!'
    ecall

    # Save all registers
    sw x0,4*0(x0)
    sw x1,4*1(x0)
    sw x2,4*2(x0)
    sw x3,4*3(x0)
    sw x4,4*4(x0)
    sw x5,4*5(x0)
    sw x6,4*6(x0)
    sw x7,4*7(x0)
    sw x8,4*8(x0)
    sw x9,4*9(x0)
    sw x10,4*10(x0)
    sw x11,4*11(x0)
    sw x12,4*12(x0)
    sw x13,4*13(x0)
    sw x14,4*14(x0)
    sw x15,4*15(x0)
    sw x16,4*16(x0)
    sw x17,4*17(x0)
    sw x18,4*18(x0)
    sw x19,4*19(x0)
    sw x20,4*20(x0)
    sw x21,4*21(x0)
    sw x22,4*22(x0)
    sw x23,4*23(x0)
    sw x24,4*24(x0)
    sw x25,4*25(x0)
    sw x26,4*26(x0)
    sw x27,4*27(x0)
    sw x28,4*28(x0)
    sw x29,4*29(x0)
    sw x30,4*30(x0)
    sw x31,4*31(x0)

    # zero all registers
    addi x0,x0,0
    addi x1,x0,0
    addi x2,x0,0
    addi x3,x0,0
    addi x4,x0,0
    addi x5,x0,0
    addi x6,x0,0
    addi x7,x0,0
    addi x8,x0,0
    addi x9,x0,0
    addi x10,x0,0
    addi x11,x0,0
    addi x12,x0,0
    addi x13,x0,0
    addi x14,x0,0
    addi x15,x0,0
    addi x16,x0,0
    addi x17,x0,0
    addi x18,x0,0
    addi x19,x0,0
    addi x20,x0,0
    addi x21,x0,0
    addi x22,x0,0
    addi x23,x0,0
    addi x24,x0,0
    addi x25,x0,0
    addi x26,x0,0
    addi x27,x0,0
    addi x28,x0,0
    addi x29,x0,0
    addi x30,x0,0
    addi x31,x0,0

    # load all registers

    lw x0,4*0(x0)
    lw x1,4*1(x0)
    lw x2,4*2(x0)
    lw x3,4*3(x0)
    lw x4,4*4(x0)
    lw x5,4*5(x0)
    lw x6,4*6(x0)
    lw x7,4*7(x0)
    lw x8,4*8(x0)
    lw x9,4*9(x0)
    lw x10,4*10(x0)
    lw x11,4*11(x0)
    lw x12,4*12(x0)
    lw x13,4*13(x0)
    lw x14,4*14(x0)
    lw x15,4*15(x0)
    lw x16,4*16(x0)
    lw x17,4*17(x0)
    lw x18,4*18(x0)
    lw x19,4*19(x0)
    lw x20,4*20(x0)
    lw x21,4*21(x0)
    lw x22,4*22(x0)
    lw x23,4*23(x0)
    lw x24,4*24(x0)
    lw x25,4*25(x0)
    lw x26,4*26(x0)
    lw x27,4*27(x0)
    lw x28,4*28(x0)
    lw x29,4*29(x0)
    lw x30,4*30(x0)
    lw x31,4*31(x0)

    .word 0
