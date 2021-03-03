#include <stdio.h>
#include <inttypes.h>

int main()
{
    volatile uint32_t* info_addr  = 0x10000100;
    volatile uint32_t* sdram_ctrl = 0x20000000;
    volatile uint32_t* sdram_mem  = 0x30000000;
    uint32_t prev_sdram = 0;
    uint32_t sdram = 0;

    uint32_t prev_log = 0;

    const uint32_t CYCLES_PER_SECOND = *info_addr;

    volatile uint32_t* addr = sdram_mem;
    uint32_t value_w = 0xdeadc0de;
    printf("Write to  0x%x: 0x%x\n", addr, value_w);
    *addr = value_w;
    for(int i=0; i<8; ++i) {
        uint32_t value_r = *addr;
        printf("Read from 0x%x: 0x%x\n", addr, value_r);
        ++addr;
    }


    // for(;;)
    // {
    //     uint32_t now = time();
    //     if(now-prev_log>5*CYCLES_PER_SECOND) {
    //         printf("*** MARK *** mdcycle=%u\n", now);
    //         prev_log = now;
    //     }

    //     sdram = *sdram_ctrl;
    //     if(sdram!=prev_sdram) {
    //         printf("mdcycle=%u : 0x%x -> 0x%x\n", now, prev_sdram, sdram);
    //         prev_sdram = sdram;
    //     }
    // }
}
