#include <stdio.h>
#include <stdlib.h>

unsigned int find_parity(unsigned int n)
{
    unsigned int parity = 0U;

    while (n != 0U) {
        parity ^= (n & 1U);
        n >>= 1U;
    }

    return parity;
}

int main(void)
{
    unsigned int number = 0U;
    int result;

    printf("Enter a non-negative integer: ");

    result = scanf("%u", &number);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (find_parity(number) == 1U) {
        printf("The parity of %u is odd.\n", number);
    } else {
        printf("The parity of %u is even.\n", number);
    }

    return EXIT_SUCCESS;
}