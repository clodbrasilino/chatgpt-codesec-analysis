#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit_position(unsigned int n)
{
    int position = 1;

    if (n == 0U)
    {
        return -1;
    }

    while ((n & 1U) == 0U)
    {
        n >>= 1U;
        position++;
    }

    return position;
}

int main(void)
{
    unsigned int values[] = { 18U, 12U, 1U, 0U, 40U };
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0U; i < count; i++)
    {
        int pos = get_rightmost_set_bit_position(values[i]);

        if (pos == -1)
        {
            if (printf("Number %u has no set bits\n", values[i]) < 0)
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (printf("Rightmost set bit of %u is at position %d\n", values[i], pos) < 0)
            {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}