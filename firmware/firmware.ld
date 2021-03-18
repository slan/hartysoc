MEMORY
{
    ram (rx) : ORIGIN = 0x80000000, LENGTH = 0x10000
}

SECTIONS
{
    .text : {
        KEEP(build/firmware/firmware.s.o(.text));
        *(.text*);
        *(.rodata*);
        *(.data*);
        *(.sdata*);
        *(.srodata*);
        *(.bss*);
        *(.sbss*);
        . = ALIGN(4);
    } > ram
    /DISCARD/ : { *(*) }
}
