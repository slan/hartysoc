    la sp, _stack
    call main
    ebreak

    la a0, 0x10000000

    la a1, _msg
_loop:
    lb a2, 0(a1)
    beqz a2, _end
    call _putc
    addi a1, a1, 1
    j _loop

_end:

#     la a0, _start_bss
#     la a1, _end_bss
# _loop_bss:
#     beq a0, a1, _start_c
#     sw x0,0(a1)
#     addi a1, a1, 4
#     j _loop_bss

_start_c:
    la sp, _stack
    call main
    ebreak
    
_putc:
    lb t0,0(a0)
    beqz t0, _putc
    sb a2,0(a0)
    ret

    .section .data
_msg:
    .string "Bonjour tout le monde !\n"
