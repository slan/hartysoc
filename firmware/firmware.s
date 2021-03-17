    # Console + ROM
    la a0, 0x10000000
    la a1, 0x20000010 # greetings
    
    call _puts

    ebreak

    # LEDs
    la a0, 0x60000000
    li t0, 0b0101
    sb t0, 0(a0)

    # RAM
    la a0, _stack
    li t0, 42
    sw t0, -4(a0)

    # VGA + LEDs
    la a0, 0x90000000
    la a1, 0x60000000
    li t0, 0
_loop:
    sw t0, 0(a0)
    srli t1, t0, 16
    sb t1, 0(a1)
    addi t0, t0, 1
    j _loop

    ebreak
    
    la a0, 0x10000000
    la a1, 0x20000010 # greetings
    
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
    lbu t0, 0(a1)
    beqz t0, _end_puts
    sb t0,0(a0)
    addi a1, a1, 1
    j _puts
_end_puts:
    ret
    
    .zero 1024
_stack:
