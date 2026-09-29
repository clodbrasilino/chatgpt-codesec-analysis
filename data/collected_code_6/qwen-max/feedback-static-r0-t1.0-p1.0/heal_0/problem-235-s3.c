#include <stdio.h>
#include <stdint.h>

uint32_t set_even_bits(uint32_t num) {
    return num | 0xAAAAAAAA;
}

int main() {
    uint32_t num = 0x12345678;
    printf("Original number: %08X\n", num);
    uint32_t result = set_even_bits(num);
    printf("Number with even bits set: %08X\n", result);
    return 0;
}