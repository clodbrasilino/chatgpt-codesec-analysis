#include <stdio.h>
#include <stdint.h>

uint32_t set_even_bits(uint32_t num) {
    uint32_t mask = 0xAAAAAAAA;
    return num | mask;
}

int main() {
    uint32_t num = 0x12345678;
    uint32_t result = set_even_bits(num);
    printf("Original number: 0x%08X\n", num);
    printf("Number with even bits set: 0x%08X\n", result);
    return 0;
}