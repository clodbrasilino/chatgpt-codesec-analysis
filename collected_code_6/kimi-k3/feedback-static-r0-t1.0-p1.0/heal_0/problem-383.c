#include <stdio.h>
#include <stdint.h>

uint32_t toggle_odd_bits(uint32_t num) {
    return num ^ 0xAAAAAAAA;
}

int main(void) {
    uint32_t num = 0x0F0F0F0F;
    uint32_t result = toggle_odd_bits(num);
    printf("Original: 0x%08X\n", num);
    printf("Toggled:  0x%08X\n", result);
    return 0;
}