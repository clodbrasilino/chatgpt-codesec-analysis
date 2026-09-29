#include <stdio.h>
#include <stdint.h>

uint32_t left_rotate_bits(uint32_t num, unsigned int d) {
    unsigned int shift = d % 32;
    if (shift == 0) {
        return num;
    }
    return (num << shift) | (num >> (32 - shift));
}

int main() {
    uint32_t num1 = 0x1A2B3C4D;
    unsigned int d1 = 8;
    
    uint32_t num2 = 64;
    unsigned int d2 = 2;
    
    uint32_t num3 = 1;
    unsigned int d3 = 66;

    printf("%u\n", left_rotate_bits(num1, d1));
    printf("%u\n", left_rotate_bits(num2, d2));
    printf("%u\n", left_rotate_bits(num3, d3));
    
    return 0;
}