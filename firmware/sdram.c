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

void pretty_print_hex_word(uint32_t word)
{
    if (word < 0x10)
        printf("0");
    if (word < 0x100)
        printf("0");
    if (word < 0x1000)
        printf("0");
    if (word < 0x10000)
        printf("0");
    if (word < 0x100000)
        printf("0");
    if (word < 0x1000000)
        printf("0");
    if (word < 0x10000000)
        printf("0");
    printf("%x", word);
}

void pretty_print_hex_byte(uint32_t byte)
{
    if (byte < 0x10)
        printf("0");
    printf("%x", byte);
}

void dump_memory_words(unsigned int n, unsigned int col)
{
    uint32_t *sdram_addr = 0x30000000;
    for (unsigned int i = 0; i < n; ++i)
    {
        uint32_t *addr_r = ((uint32_t *)sdram_addr) + i;
        pretty_print_hex_word(*addr_r);
        printf((i + 1) % col ? " " : "\n");
    }
    if ((n % col) != 0)
        printf("\n");
}

void dump_memory_bytes(unsigned int n, unsigned int col)
{
    uint32_t *sdram_addr = 0x30000000;
    for (unsigned int i = 0; i < n; ++i)
    {
        pretty_print_hex_byte(*((uint8_t *)sdram_addr + i));
        printf((i + 1) % col ? " " : "\n");
    }
    if ((n % col) != 0)
        printf("\n");
}

void dump_memory()
{
    dump_memory_bytes(64, 16);
}

int main()
{
    volatile uint32_t *info_addr = 0x10000100;
    const uint32_t CYCLES_PER_SECOND = *info_addr;

    volatile uint32_t *sdram_ctrl = 0x20000000;
    uint32_t *sdram_addr = 0x30000000;

    printf("-----------------------------------------------\n");

    dump_memory();

    printf("\nWriting...\n");

    for (int i = 0; i < 32; ++i)
    {
        uint8_t value = i;
        (*((uint8_t *)sdram_addr + i)) = value;
        pretty_print_hex_byte(value);
        printf((i + 1) % 16 ? " " : "\n");
    }

    printf("\nReading...\n");

    dump_memory();

    printf("-----------------------------------------------\n");

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
