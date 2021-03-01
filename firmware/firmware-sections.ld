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
        *(.data*);
        . = ALIGN(4);
    } > rom
    .rodata : {
        *(.rodata*);
        . = ALIGN(4);
    } > rom
    .bss : {
        *(.bss*);
        . = ALIGN(4);
    } > rom
    .sbss : {
        *(.sbss*);
        . = ALIGN(4);
    } > rom
    .stack : {
        . = . + 1024;
        _stack = .;
    } > rom
}
