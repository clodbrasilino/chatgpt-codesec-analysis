#include <stdio.h>
#include <stdlib.h>

static unsigned int highest_set_bit_mask(unsigned int n)
{
    unsigned int mask = 0U;

    while (n != 0U) {
        mask = n & (~n + 1U);
        n &= (n - 1U);
    }

    return mask;
}

static unsigned int toggle_first_last(unsigned int n)
{
    unsigned int high;

    if (n == 0U) {
        return n;
    }

    high = highest_set_bit_mask(n);
    n ^= high;
    n ^= 1U;

    return n;
}

int main(void)
{
    unsigned int number = 0U;
    unsigned int result;

    printf("Enter a non-negative number: ");

    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = toggle_first_last(number);

    if (printf("Original: %u\nResult:   %u\n", number, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}