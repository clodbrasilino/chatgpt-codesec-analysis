#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_odd_parity(unsigned int number)
{
    unsigned int count = 0;

    while (number != 0U) {
        count += (number & 1U);
        number >>= 1U;
    }

    return (count % 2U) == 1U;
}

int main(void)
{
    unsigned int value = 0U;
    int result = 0;

    printf("Enter a non-negative integer: ");

    result = scanf("%u", &value);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (has_odd_parity(value)) {
        printf("%u has odd parity.\n", value);
    } else {
        printf("%u has even parity.\n", value);
    }

    return EXIT_SUCCESS;
}