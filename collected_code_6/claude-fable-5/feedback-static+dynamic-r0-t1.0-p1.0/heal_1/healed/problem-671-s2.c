#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int set_rightmost_unset_bit(unsigned int n)
{
    if (n == 0U) {
        return 1U;
    }
    if ((n & (n + 1U)) == 0U) {
        return n;
    }
    return n | (n + 1U);
}

int main(void)
{
    unsigned int value = 0U;
    unsigned int result = 0U;

    printf("Enter a non-negative integer: ");
    if (scanf("%u", &value) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = set_rightmost_unset_bit(value);
    printf("Input:  %u\n", value);
    printf("Output: %u\n", result);

    return EXIT_SUCCESS;
}