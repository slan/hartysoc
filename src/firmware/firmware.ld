MEMORY
{
    rom (rx) : ORIGIN = 0x00000000, LENGTH = 0x1000
}

SECTIONS
{
    .text : {
        KEEP(build/firmware/firmware.s.o(.text));
        *(*);
        . = ALIGN(4);
        . = . + 1024;
        _stack = .;
    } > rom
}
