#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit_position(unsigned int n)
{
    int position;

    if (n == 0U)
    {
        return -1;
    }

    position = 1;
    while ((n & 1U) == 0U)
    {
        n >>= 1U;
        position++;
    }

    return position;
}

int main(void)
{
    unsigned int values[] = {18U, 12U, 7U, 0U, 128U};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    for (i = 0; i < count; i++)
    {
        result = get_rightmost_set_bit_position(values[i]);
        if (result == -1)
        {
            if (printf("Number %u has no set bits\n", values[i]) < 0)
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (printf("Rightmost set bit of %u is at position %d\n", values[i], result) < 0)
            {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}