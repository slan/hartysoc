#include <stdio.h>
#include <inttypes.h>

int main()
{
    volatile uint32_t* sdram_addr = 0x10000004;
    uint32_t prev_sdram = 0;
    uint32_t sdram = 0;

    uint32_t prev_log = 0;

    const uint32_t CYCLE_PER_SECOND = 100e6*16/128;

    printf("mdcycle=%u\n", time());
    for(;;)
    {
        uint32_t now = time();
        if(now-prev_log>5*CYCLE_PER_SECOND) {
            printf("*** MARK *** mdcycle=%u\n", now);
            prev_log = now;
        }

        sdram = *sdram_addr;
        if(sdram!=prev_sdram) {
            printf("mdcycle=%u : 0x%x -> 0x%x\n", now, prev_sdram, sdram);
            prev_sdram = sdram;
        }
    }
}
