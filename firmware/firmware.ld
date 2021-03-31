MEMORY
{
    rom (rx ) : ORIGIN = 0x80000000, LENGTH = 32K
    ram (rwx) : ORIGIN = 0x00000000, LENGTH = 32K
}

SECTIONS
{
    .firmware : {
        KEEP(build/firmware/firmware.s.o(*));
        . = ALIGN(4);
    } > rom
    .main : {
        *(.text*);
        *(.rodata*);
        *(.data*);
        *(.sdata*);
        *(.srodata*);
        *(.bss*);
        *(.sbss*);
        . = ALIGN(4);
   } > rom AT> rom

    _size_main = SIZEOF(.main);

    /DISCARD/ : { *(*) }
}
