#include <stdio.h>
#include <stdint.h>

uint32_t set_odd_bits(uint32_t num) {
    uint32_t mask = 0xAAAAAAAA;
    return num | mask;
}

int main() {
    uint32_t number = 0x12345678;
    uint32_t result = set_odd_bits(number);
    printf("Original: %08X, Set Odd Bits: %08X\n", number, result);
    return 0;
}