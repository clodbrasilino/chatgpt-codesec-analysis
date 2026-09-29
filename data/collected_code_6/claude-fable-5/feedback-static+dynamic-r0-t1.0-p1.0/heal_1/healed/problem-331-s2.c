#include <stdio.h>
#include <stdlib.h>

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