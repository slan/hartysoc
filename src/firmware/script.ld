/*
MEMORY
{
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 0x400
    RAM (rw) : ORIGIN = 0x00001000, LENGTH = 0x400
}
*/
SECTIONS
{
   .firmware : {
        build/firmware/*.o(.text);
    }
}