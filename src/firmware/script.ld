SECTIONS
{
    .text : {
        build/firmware/crt0.s.o(.text);
        *(.text*);
    }
    .data : {
        *(.rodata);
        *(.data);
        *(.bss);
        *(.sbss);
        . = ALIGN(4);
        . = . + 1024;
        _stack = .;
    }
}