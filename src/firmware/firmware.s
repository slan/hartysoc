start:
    li a1, 6
loop:
    add a2, a1, a1
    add a3, a3, a2
    addi a1, a1, -1
    bnez a1, loop

    li a7,1

    li a0,'!'
    ecall

    la a0,msg
    lb a1,0(a0)
    lb a2,1(a0)
msg:
    .string "Bonjour !"
end:
    #.zero 4096-(end-start)
