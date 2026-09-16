#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 40, got <no output>
  *  test case 0 failed: expected 64, got <no output>
  *  test case 2 failed: expected 792, got <no output>
  */

uint32_t left_rotate_bits(uint32_t value, unsigned int shift)
{
    const unsigned int bit_width = sizeof(value) * CHAR_BIT;
    shift %= bit_width;
    
    if (shift == 0)
    {
        return value;
    }
    
    return (value << shift) | (value >> (bit_width - shift));
}

int main(void)
{
    uint32_t number = 0x12345678U;
    unsigned int rotate_amount = 8U;
    uint32_t result = left_rotate_bits(number, rotate_amount);
    
    printf("Original: 0x%08X\n", number);
    printf("Rotated left by %u: 0x%08X\n", rotate_amount, result);
    
    return 0;
}