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
    printf("%u\n", left_rotate_bits(0x80000000U, 31U));
    printf("%u\n", left_rotate_bits(0x00000001U, 6U));
    printf("%u\n", left_rotate_bits(0x000000FFU, 5U));
    
    return 0;
}