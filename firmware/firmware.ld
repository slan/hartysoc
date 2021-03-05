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
        . = ALIGN(4);
        . = . + 256;
       _stack = .;
    }
    /DISCARD/ : { *(*) }
}
