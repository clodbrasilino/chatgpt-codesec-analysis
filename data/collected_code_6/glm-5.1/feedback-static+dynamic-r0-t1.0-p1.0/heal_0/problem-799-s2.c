#include <stdio.h>
#include <stdint.h>

uint32_t left_rotate_bits(uint32_t num, unsigned int d) {
    unsigned int shift = d % 32;
    return (num << shift) | (num >> (32 - shift));
}

int main() {
    uint32_t num = 0x1A2B3C4D;
    unsigned int d = 8;
    
    uint32_t result = left_rotate_bits(num, d);
    
    printf("%u\n", result);
    
    return 0;
}