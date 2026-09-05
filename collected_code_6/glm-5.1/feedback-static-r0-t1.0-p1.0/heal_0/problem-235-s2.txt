#include <stdio.h>
#include <stdint.h>

uint32_t set_even_bits(uint32_t n) {
    uint32_t mask = 0x55555555;
    return n | mask;
}

int main(void) {
    uint32_t input = 0;
    uint32_t result = set_even_bits(input);
    printf("%u\n", result);
    return 0;
}