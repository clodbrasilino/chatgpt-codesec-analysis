#include <stdio.h>
#include <stdlib.h>

unsigned int find_parity(unsigned int n)
{
    unsigned int parity = 0U;

    while (n != 0U)
    {
        parity ^= (n & 1U);
        n >>= 1U;
    }

    return parity;
}

int main(void)
{
    unsigned int number = 0U;

    printf("Enter a non-negative integer: ");

    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (find_parity(number) == 0U)
    {
        printf("The number %u has even parity.\n", number);
    }
    else
    {
        printf("The number %u has odd parity.\n", number);
    }

    return EXIT_SUCCESS;
}