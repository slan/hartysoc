#include <inttypes.h>

int main()
{
    volatile uint32_t i=0x01234567;
    printf(((*((uint8_t*)(&i))) == 0x67) ? "little" : "big");

    uint8_t    swaptest[2] = {1,0};
    if ( *(uint16_t *)swaptest == 1)
        printf("little");
    else
        printf("big");
}