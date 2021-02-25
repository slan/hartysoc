SECTIONS
{
    .text : {
        KEEP(build/firmware/start.o(.text));
        *(.text);
    }
    .data : {
        *(.data);
        . = ALIGN(4);
    }
    .stack : {
        . = . + 1024;
        _stack = .;
    }
    /DISCARD/ : {
        *(*);
    }
}
