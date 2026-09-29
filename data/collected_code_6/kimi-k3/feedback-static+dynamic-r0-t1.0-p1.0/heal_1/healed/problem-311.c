#include <stdio.h>
#include <limits.h>

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