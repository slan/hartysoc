#include <stdio.h>
#include <inttypes.h>

unsigned lfsr1(void)
{
    const uint16_t start_state = 0xACE1u; /* Any nonzero start state will work. */
    static uint16_t lfsr = start_state;

    uint16_t bit; /* Must be 16-bit to allow bit<<15 later in the code */

    /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) /* & 1u */;
    lfsr = (lfsr >> 1) | (bit << 15);

    return lfsr;
}

int main()
{
    volatile uint32_t *info_addr = 0x10000100;
    const uint32_t CYCLES_PER_SECOND = *info_addr;

    volatile uint32_t *sdram_ctrl = 0x20000000;
    uint32_t *sdram_addr = 0x30000000;

    printf("-----------------------------------------------\n");
    const int LOOPS = 256;
    for (int j = 0; j < LOOPS; ++j)
    {
        uint8_t *addr_r = ((uint8_t*)sdram_addr)+j;
        if(*addr_r<0x10) printf("0");
        printf("%x ",*addr_r);
        if((j%16)==15) printf("\n");
    }
    printf("\n");
    for (int j = 0; j < LOOPS/4; ++j)
    {
        uint32_t *addr_r = ((uint32_t*)sdram_addr)+j;
        if(*addr_r<0x10) printf("0");
        if(*addr_r<0x100) printf("0");
        if(*addr_r<0x1000) printf("0");
        if(*addr_r<0x10000) printf("0");
        if(*addr_r<0x100000) printf("0");
        if(*addr_r<0x1000000) printf("0");
        if(*addr_r<0x10000000) printf("0");
        printf("%x ",*addr_r);
        if((j%4)==3) printf("\n");
    }


}
/*
    for (int i = 0; i < LOOPS; ++i)
    {
        uint32_t value_w = (lfsr1() << 16) | lfsr1();
        uint32_t *addr_w = sdram_addr+i;
        printf("Write to 0x%x: 0x%x\n", addr_w, value_w);
    }

    uint32_t instret = insn();
    uint32_t cycle = time();

    printf("cycle=%u insn=%u\n", cycle, instret);

    float cpi = (float)cycle / instret;

    uint32_t digits = 1e9;

    uint32_t cpi_i = (uint32_t)cpi;
    uint32_t cpi_f = (uint32_t)(cpi * digits - cpi_i * digits);

    printf("cpi=%u.", cpi_i);
    while (cpi_f < digits)
    {
        printf("0");
        digits /= 10;
    }
    printf("%u\n", cpi_f);
}
*/