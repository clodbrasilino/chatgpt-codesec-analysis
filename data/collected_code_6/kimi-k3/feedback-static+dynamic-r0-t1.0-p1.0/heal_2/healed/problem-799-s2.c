#include <stdio.h>
#include <stdint.h>
#include <limits.h>

uint32_t left_rotate(uint32_t value, unsigned int shift)
{
    const unsigned int bits = sizeof(value) * CHAR_BIT;
    shift %= bits;
    if (shift == 0) {
        return value;
    }
    return (value << shift) | (value >> (bits - shift));
}

int main(void)
{
    uint32_t value = 0x12345678U;
    unsigned int shift = 4;
    
    printf("%u\n", (unsigned int)left_rotate(value, shift));
    
    return 0;
}