#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 13
  *  test case 0 failed: expected 14, got 11
  *  test case 2 failed: expected 15, got 31
  */

unsigned int set_leftmost_unset_bit(unsigned int n)
{
    unsigned int temp;
    unsigned int mask;

    if (n == UINT_MAX)
    {
        return n;
    }

    temp = ~n;
    mask = temp & (0U - temp);
    n |= mask;

    return n;
}

int main(void)
{
    const unsigned int test_cases[] = {0x7FFFFFFFU, 0x00000000U, 0xFFFFFFFFU};
    int num_tests = 3;
    int i;

    for (i = 0; i < num_tests; i++)
    {
        unsigned int result = set_leftmost_unset_bit(test_cases[i]);
        printf("%u\n", result);
    }

    return 0;
}