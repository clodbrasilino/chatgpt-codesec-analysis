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
    return (value << shift) | (value >> (bits - shift));
}

int main(void)
{
    uint32_t num = 0x12345678U;
    unsigned int rotate_by = 8U;
    uint32_t result = left_rotate(num, rotate_by);
    
    (void)printf("Original: 0x%08X\n", num);
    (void)printf("Rotated by %u: 0x%08X\n", rotate_by, result);
    
    return 0;
}