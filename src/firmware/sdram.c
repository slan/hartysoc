#include <inttypes.h>

int main()
{
    volatile uint32_t* sdram_addr = 0x10000004;
    uint32_t prev_sdram = 0;
    uint32_t sdram = 0;

    printf("mdcycle=%d\n", time());
    for(;;)
    {
        sdram = *sdram_addr;
        if(sdram!=prev_sdram) {
            printf("mdcycle=%d : %d -> %d\n", time(), prev_sdram, sdram);
            prev_sdram = sdram;
        }
    }
}
