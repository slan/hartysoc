    addi x7, x0, 0
    addi x6, x0, 6
loop:
    add x5, x6, x6
    add x7, x7, x5
    addi x6, x6, -1
    bne x6, x0, loop

    sw x7,28(x0)
    lw x28,28(x0)