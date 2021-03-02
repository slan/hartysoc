MEMORY
{
    rom (rx) : ORIGIN = 0x00000000, LENGTH = 0x10000
}

SECTIONS
{
    .text : {
        KEEP(build/firmware/firmware.s.o(.text));
        *(.text*);
    } > rom
    .data : {
        *(.rodata*);
        *(.data*);
        *(.bss*);
        *(.sbss*);
        . = ALIGN(4);
        . = . + 1024;
        _stack = .;
    } > rom
}
