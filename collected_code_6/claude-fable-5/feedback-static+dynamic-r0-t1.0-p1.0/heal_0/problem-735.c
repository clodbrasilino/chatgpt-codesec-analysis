#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int n);

unsigned int toggle_middle_bits(unsigned int n)
{
    unsigned int mask;

    if (n <= 3U) {
        return n;
    }

    mask = n;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;

    mask >>= 1;
    mask &= ~1U;

    return n ^ mask;
}

int main(void)
{
    unsigned int number;
    unsigned int result;

    printf("Enter a non-negative integer: ");
    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = toggle_middle_bits(number);

    printf("Original number: %u\n", number);
    printf("After toggling middle bits: %u\n", result);

    return EXIT_SUCCESS;
}