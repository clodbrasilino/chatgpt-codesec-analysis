#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 40, got <no output>
  *  test case 0 failed: expected 64, got <no output>
  *  test case 2 failed: expected 792, got <no output>
  */

uint32_t left_rotate(uint32_t value, unsigned int shift)
{
    const unsigned int bits = sizeof(value) * CHAR_BIT;
    shift %= bits;
    return (value << shift) | (value >> (bits - shift));
}

int main(void)
{
    uint32_t value = 0x12345678U;
    unsigned int shift = 4;
    
    printf("Original: 0x%08X\n", value);
    printf("Rotated:  0x%08X\n", left_rotate(value, shift));
    
    return 0;
}