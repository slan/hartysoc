    # la a0, 0x30000000
    
    # li t0, 0x12345678
    # sw t0,0(a0)
    # lw t1,0(a0)
    
    # li t2, 0x90abcdef
    # sw t2, 4(a0)
    # lw t3, 4(a0)

    # nop

    # ebreak
    j _main

    la a0, 0x10000000

    la a1, 0x10000104 # greetings
    call _puts

    la a1, _msg_waiting
    call _puts

    la a2, 0x20000000
_wait_sdram:
    lw t0,0(a2)
    xori t0, t0, 0xf
    bnez t0, _wait_sdram

    la a1, _msg_ok
    call _puts

    #####

    la a1, _msg_sdram_test
    call _puts

    la a2, 0x30000000
    li t0, 0x61626364
        
    sw t0, 0(a2)
    
    lw t1, 0(a2)
    bne t0,t1, _nok
    la a1, _msg_ok
    j _end_test
_nok:
    la a1, _msg_nok
_end_test:
    call _puts

    #####

_main:
    la sp, _stack
    li a0, 0
    call main
    ebreak

    # IN: a0 uart
    # IN: a1 string
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

    .section .rodata
_msg_waiting:
    .string "SDRAM RDY..."
_msg_sdram_test:
    .string "SDRAM R/W..."
_msg_ok:
    .string "OK\n"
_msg_nok:
    .string "Oops\n"
_buf:
    .string "????\n"

