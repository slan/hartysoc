.section .text

    la sp,_stack
    addi sp, sp, -4
    li a0,0x12
    sb a0,0(sp)
    lw a1,0(sp)
    .word 0

    la sp,_stack
    la a0,0x10000000
    li a1,'>'
    call putc
    li a1,'\n'
    call putc

    call main

    la a0,0x10000000
    li a1,'\n'
    call putc
    li a1,'<'
    call putc
    li a1,'\n'
    call putc
.word 0x00000000
putc:
    lb a2,0(a0)
    beqz a2,putc
    sb a1,0(a0)
    ret
