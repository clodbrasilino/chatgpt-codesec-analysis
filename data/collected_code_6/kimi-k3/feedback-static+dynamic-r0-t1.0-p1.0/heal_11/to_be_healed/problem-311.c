#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 4294967279
  *  test case 1 failed: expected 14, got 4294967276
  *  test case 0 failed: expected 14, got 4294967274
  */

unsigned int set_leftmost_unset_bit(unsigned int n)
{
    if (n == UINT_MAX)
    {
        return n;
    }
    
    unsigned int temp = n;
    unsigned int shift = 1;
    while (shift < sizeof(unsigned int) * CHAR_BIT)
    {
        temp |= temp >> shift;
        shift <<= 1;
    }
    temp = ~temp;
    temp &= (temp - 1);
    n |= temp;
    
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