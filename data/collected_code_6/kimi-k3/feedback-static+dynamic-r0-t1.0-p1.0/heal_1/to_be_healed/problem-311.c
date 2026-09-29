#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 14, got <no output>
  *  test case 1 failed: expected 14, got <no output>
  */

unsigned int set_leftmost_unset_bit(unsigned int n)
{
    unsigned int mask = 1U << (sizeof(unsigned int) * CHAR_BIT - 1U);

    while (mask != 0U)
    {
        if ((n & mask) == 0U)
        {
            n |= mask;
            break;
        }
        mask >>= 1U;
    }

    return n;
}

int main(void)
{
    unsigned int value = 0x7FFFFFFFU;
    unsigned int result = set_leftmost_unset_bit(value);

    printf("Original: 0x%X\n", value);
    printf("Modified: 0x%X\n", result);

    return 0;
}