#include <stdio.h>
#include <stdlib.h>

int has_even_parity(unsigned int n)
{
    unsigned int count = 0;

    while (n != 0U) {
        count += (n & 1U);
        n >>= 1U;
    }

    return (count % 2U) == 0U;
}

int main(void)
{
    unsigned int number = 0U;
    int result = 0;

    printf("Enter a non-negative integer: ");

    result = scanf("%u", &number);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (has_even_parity(number)) {
        printf("%u has even parity.\n", number);
    } else {
        printf("%u has odd parity.\n", number);
    }

    return EXIT_SUCCESS;
}