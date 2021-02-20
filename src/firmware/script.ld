SECTIONS
{
    .root : { build/firmware/crt0.s.o(.text) *(.text) }
}