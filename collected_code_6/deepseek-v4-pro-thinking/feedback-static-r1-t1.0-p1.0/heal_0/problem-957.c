#include <stdio.h>

int get_position_of_rightmost_set_bit(unsigned int value)
{
    unsigned int position = 0;

    if (value == 0)
    {
        return -1;
    }

    while ((value & 1U) == 0U)
    {
        value >>= 1U;
        position++;
    }

    return (int)position;
}

int main(void)
{
    unsigned int test_values[] = {0U, 1U, 2U, 3U, 4U, 8U, 18U};
    int i;

    for (i = 0; i < (int)(sizeof(test_values) / sizeof(test_values[0])); i++)
    {
        printf("Rightmost set bit position of %u is %d\n",
               test_values[i],
               get_position_of_rightmost_set_bit(test_values[i]));
    }

    return 0;
}