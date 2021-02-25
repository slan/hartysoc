    .globl main

main:
    la a0,0x10000000

    la a1, _msg
_loop:
    lb a2, 0(a1)
    beqz a2, _end
    call _putc
    addi a1, a1, 1
    j _loop

_end:
    ebreak

_putc:
    lb t0,0(a0)
    beqz t0, _putc
    sb a2,0(a0)
    ret

    .section .data
_msg:
    .string "Bonjour tout le monde !\n"
