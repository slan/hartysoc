SECTIONS
{
    .text : {
        KEEP(build/firmware/firmware.s.o(.text));
        *(.text*);
    }
    .data : {
        *(.rodata*);
        *(.data*);
        *(.sdata*);
        *(.srodata*);
    }
    /DISCARD/ : { *(*) }
}
