SECTIONS
{
    .firmware : {
        build/firmware/crt0.s.o(.text);
        *(.text);
        *(.data);
        . = . + 1024;
        end = .;
        _stack = .;
    }
}