    rdinstret t5

    la a0, 0x20000000
_wait_sdram:
    lw t0, 0(a0)
    andi t0, t0, 0x2
    beqz t0, _wait_sdram

    rdinstret t6

    la a0, 0x30000000
    sub t6, t6, t5
    sw t6, 0(a0)

    la a0, 0x10000000

    la a1, 0x10000110 # greetings
    call _puts

    #####

    la sp, _stack
    li a0, 0

    call main
    
    ebreak

    #####

    # IN: a0 uart addr
    # IN: a1 message addr
_puts:
    lb t0, 0(a1)
    beqz t0, _end_puts
_putc:
    lb t1,0(a0)
    beqz t1, _putc
    sb t0,0(a0)
    addi a1, a1, 1
    j _puts
_end_puts:
    ret

    .zero 1024
_stack:
