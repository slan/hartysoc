    la a0, _addr_main
    la a2, _size_main

    call _memcpy

    la a0, 0x10000000
    la a1, 0x20000010  # Greetings (SOCInfo)
    
    call _puts

    #####

    la sp, _stack
    li a0, 0

    call main
    
    ebreak

    #####

_printx:
    lb t0, 0(a0)
    beqz t0, _printx
    li t1, 10
    srli t0, a1, 4
    bltu t0, t1, _lt10_high
    addi t0, t0, 'a'-'0'-10
_lt10_high:
    addi t0, t0, '0'
    sb t0, 0(a0)
    andi t0, a1, 0x0f
    bltu t0, t1, _lt10_low
    addi t0, t0, 'a'-'0'-10
_lt10_low:
    addi t0, t0, '0'
    sb t0, 0(a0)
    li t0, '\n'
    sb t0, 0(a0)
    ret

    # IN: a0 uart addr
    # IN: a1 message addr
_puts:
    lb t0, 0(a0)
    beqz t0, _puts  # Active wait for UART to get accurate CPI
    lbu t0, 0(a1)
    beqz t0, _puts_ret
    sb t0,0(a0)
    addi a1, a1, 1
    j _puts
_puts_ret:
    ret
    
    # IN: a0: src
    # IN: a1: dst
    # IN: a2: size
_memcpy:
    beqz a2, _memcpy_ret
    lw t0, 0(a0)
    sw t0, 0(a1)
    addi a0, a0, 4
    addi a1, a1, 4
    addi a2, a2, -4
    j _memcpy
_memcpy_ret:
    ret
    