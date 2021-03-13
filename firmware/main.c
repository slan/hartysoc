#include <stdio.h>
#include <inttypes.h>

int main(int argc, char* argv[])
{
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

    return 0;
}
