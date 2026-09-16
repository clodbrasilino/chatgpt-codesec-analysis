#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int count_unset_bits(unsigned int number)
{
    unsigned int count = 0U;
    unsigned int total_bits = (unsigned int)(sizeof(unsigned int) * CHAR_BIT);
    unsigned int i;

    for (i = 0U; i < total_bits; i++)
    {
        if ((number & (1U << i)) == 0U)
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    unsigned int number = 0U;
    unsigned int result = 0U;
    int scan_status = 0;

    printf("Enter a non-negative integer: ");

    scan_status = scanf("%u", &number);
    if (scan_status != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = count_unset_bits(number);

    if (printf("Number of unset bits in %u: %u\n", number, result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}