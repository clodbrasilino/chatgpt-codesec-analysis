#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 2 failed: expected 15, got 2147483663
  *  test case 0 failed: expected 14, got 2147483658
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
    /* Possible weaknesses found:
     *  Variable 'test_cases' can be declared as const array [constVariable]
     */
    unsigned int test_cases[] = {0x7FFFFFFFU, 0x00000000U, 0xFFFFFFFFU};
    int num_tests = 3;
    int i;

    for (i = 0; i < num_tests; i++)
    {
        unsigned int result = set_leftmost_unset_bit(test_cases[i]);
        printf("%u\n", result);
    }

    return 0;
}