SECTIONS
{
    .firmware : {
        build/firmware/crt0.s.o(.text);
        *(.text);
        *(*);
        end = .;
        . = . + 16*1024;
        . = ALIGN(4);
        _stack = .;
    }
}