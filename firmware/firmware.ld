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
   } > ram AT> rom                          /* Run in RAM, include in ROM */
    
    _addr_main = LOADADDR(.main);           /* LOADADDR gives the LMA, i.e the offset from rom start */
    _size_main = SIZEOF(.main);

    _stack = ADDR(.main);                   /* ADDR gives the VMA, i.e the start address of the section */
    _stack = _stack + _size_main + 1024;

    /DISCARD/ : { *(*) }
}
