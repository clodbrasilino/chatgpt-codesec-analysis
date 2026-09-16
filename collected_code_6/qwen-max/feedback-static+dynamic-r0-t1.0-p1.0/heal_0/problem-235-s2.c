#include <stdio.h>
#include <stdint.h>

uint32_t set_even_bits(uint32_t num) {
    return num | 0xAAAAAAAA;
}

int main() {
    uint32_t number = 0x12345678;
    uint32_t result = set_even_bits(number);
    printf("Original: 0x%08X\n", number);
    printf("Result:   0x%08X\n", result);
    return 0;
}