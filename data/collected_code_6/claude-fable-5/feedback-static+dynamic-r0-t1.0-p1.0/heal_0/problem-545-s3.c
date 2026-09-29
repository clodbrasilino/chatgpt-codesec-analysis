#include <stdio.h>
#include <stdlib.h>

static unsigned int toggle_first_and_last_bits(unsigned int n)
{
    unsigned int highest;

    if (n == 0U) {
        return 1U;
    }

    highest = n;
    highest |= highest >> 1;
    highest |= highest >> 2;
    highest |= highest >> 4;
    highest |= highest >> 8;
    highest |= highest >> 16;
    highest = highest - (highest >> 1);

    n ^= 1U;
    n ^= highest;

    return n;
}

int main(void)
{
    unsigned int number;
    unsigned int result;

    printf("Enter a non-negative number: ");
    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = toggle_first_and_last_bits(number);

    printf("Original number: %u\n", number);
    printf("After toggling first and last bits: %u\n", result);

    return EXIT_SUCCESS;
}