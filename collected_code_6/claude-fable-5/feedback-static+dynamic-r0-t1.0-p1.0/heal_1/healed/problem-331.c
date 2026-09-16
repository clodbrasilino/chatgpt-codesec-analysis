#include <stdio.h>
#include <limits.h>

unsigned int count_unset_bits(unsigned int number)
{
    unsigned int count = 0U;

    if (number == 0U)
    {
        return 1U;
    }

    while (number > 0U)
    {
        if ((number & 1U) == 0U)
        {
            count++;
        }
        number >>= 1U;
    }

    return count;
}

int main(void)
{
    unsigned int number = 0U;
    unsigned int result = 0U;

    printf("Enter a non-negative number: ");

    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    result = count_unset_bits(number);

    printf("Number of unset bits in %u is %u\n", number, result);

    return 0;
}