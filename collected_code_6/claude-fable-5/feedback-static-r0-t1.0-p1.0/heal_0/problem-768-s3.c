#include <stdio.h>
#include <stdlib.h>

static int has_odd_parity(unsigned int value)
{
    int count = 0;

    while (value != 0U)
    {
        count += (int)(value & 1U);
        value >>= 1U;
    }

    return (count % 2) != 0;
}

int main(void)
{
    unsigned int number = 0U;
    int result = 0;

    printf("Enter a non-negative number: ");

    result = scanf("%u", &number);
    if (result != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (has_odd_parity(number))
    {
        printf("%u has odd parity.\n", number);
    }
    else
    {
        printf("%u has even parity.\n", number);
    }

    return EXIT_SUCCESS;
}