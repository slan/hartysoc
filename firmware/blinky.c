#include <stdio.h>

int main()
{
    volatile uint32_t *info_addr = 0x20000000;
    const uint32_t CYCLES_PER_SECOND = *info_addr;
    
    uint32_t *leds = 0x60000000;
    uint32_t t0 = time();
    for(;;) {
        uint32_t dt;
        do {
            dt = time()-t0;
        } while(dt<(CYCLES_PER_SECOND/2)-4);
        t0 = time();
        *leds = ~*leds & 1;
    }
}
