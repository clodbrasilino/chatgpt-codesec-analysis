#include <stdio.h>
#include <stdint.h>
#include <limits.h>

uint32_t left_rotate(uint32_t value, unsigned int shift)
{
    const unsigned int bits = sizeof(value) * CHAR_BIT;
    shift %= bits;
    if (shift == 0U) {
        return value;
    }
    return (uint32_t)((value << shift) | (value >> (bits - shift)));
}

int main(void)
{
    printf("%u\n", left_rotate(0x00000001U, 6U));
    printf("%u\n", left_rotate(0x00000001U, 0U));
    printf("%u\n", left_rotate(0x00000001U, 2U));
    printf("%u\n", left_rotate(0x00000001U, 3U));
    printf("%u\n", left_rotate(0x00000001U, 4U));
    printf("%u\n", left_rotate(0x00000001U, 5U));
    
    return 0;
}