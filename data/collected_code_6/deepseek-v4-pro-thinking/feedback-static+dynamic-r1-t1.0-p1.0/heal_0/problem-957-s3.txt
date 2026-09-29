#include <stdio.h>

int rightmost_set_bit_position(unsigned int n)
{
    int pos = 0;

    if (n == 0)
    {
        return -1;
    }

    while ((n & 1U) == 0U)
    {
        n >>= 1;
        pos++;
    }

    return pos;
}

int main(void)
{
    unsigned int test_values[] = {0U, 1U, 2U, 3U, 8U, 12U, 128U};
    size_t i;
    size_t count = sizeof(test_values) / sizeof(test_values[0]);

    for (i = 0; i < count; i++)
    {
        int pos = rightmost_set_bit_position(test_values[i]);

        if (pos == -1)
        {
            printf("rightmost_set_bit_position(%u) = -1\n", test_values[i]);
        }
        else
        {
            printf("rightmost_set_bit_position(%u) = %d\n", test_values[i], pos);
        }
    }

    return 0;
}