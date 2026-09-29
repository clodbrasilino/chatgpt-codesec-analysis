#include <stdio.h>
#include <stdlib.h>

int find_parity(unsigned int n)
{
    int parity = 0;

    while (n != 0U) {
        parity ^= 1;
        n &= (n - 1U);
    }

    return parity;
}

int main(void)
{
    unsigned int number = 0U;
    int result;

    printf("Enter a non-negative integer: ");

    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = find_parity(number);

    if (result == 1) {
        printf("The number %u has odd parity.\n", number);
    } else {
        printf("The number %u has even parity.\n", number);
    }

    return EXIT_SUCCESS;
}