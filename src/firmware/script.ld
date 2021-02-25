MEMORY
{
    rom (rx) : ORIGIN = 0x20000000, LENGTH = 0x1000
}

SECTIONS
{
    .text : {
        KEEP(build/firmware/start.o(.text));
        *(.text);
    } > rom
    .data : {
        *(.data);
        . = ALIGN(4);
    } > rom
    .stack : {
        . = . + 1024;
        _stack = .;
    } > rom
    /DISCARD/ : {
        *(*);
    }
}
