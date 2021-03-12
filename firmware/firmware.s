    la a0, 0x10000000
    li t0, '!'
    sb t0, 0(a0)
    ebreak
    
    la a0, 0x10000000
    la a1, 0x20000010 # greetings
    
    call _puts

    ebreak

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
