#include <stdio.h>
#include <limits.h>

unsigned int set_leftmost_unset_bit(unsigned int n)
{
    unsigned int mask;
    /* Possible weaknesses found:
     *  Assignment 'temp=~n', assigned value is greater than 0
     */
    unsigned int temp = ~n;

    /* Possible weaknesses found:
     *  Condition 'temp==0U' is always false
     *  Condition 'temp==0U' is always false [knownConditionTrueFalse]
     */
    if (temp == 0U)
    {
        return n;
    }

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