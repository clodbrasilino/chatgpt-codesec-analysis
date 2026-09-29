#include <stdio.h>
#include <stdint.h>

uint32_t toggle_even_bits(uint32_t num) {
    uint32_t mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main() {
    uint32_t num = 0b10101010101010101010101010101010;
    uint32_t result = toggle_even_bits(num);
    printf("Original: %u, Toggled Even Bits: %u\n", num, result);
    return 0;
}