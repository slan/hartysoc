SECTIONS
{
    .text : {
        KEEP(build/firmware/firmware.s.o(.text));
        *(.text*);
    }
    .data : {
        *(.rodata*);
        *(.data*);
        . = ALIGN(4);
        . = . + 512;
       _stack = .;
    }
    /DISCARD/ : { *(*) }
}
