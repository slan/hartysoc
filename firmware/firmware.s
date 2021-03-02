    la a0, 0x10000000
    la a1, 0x10000100

_puts:
    lb a2, 0(a1)
    beqz a2, _end_puts

_putc:
    lb t0,0(a0)
    beqz t0, _putc
    sb a2,0(a0)

    addi a1, a1, 1
    j _puts
_end_puts:

    la sp, _stack
    li a0, 0
    call main
    ebreak
