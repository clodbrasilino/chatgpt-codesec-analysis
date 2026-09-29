#include <stdio.h>
#include <stdlib.h>

unsigned int set_rightmost_unset_bit(unsigned int n)
{
    if (~n == 0U) {
        return n;
    }
    return n | (n + 1U);
}

int main(void)
{
    unsigned int value = 0U;
    int result = 0;

    printf("Enter an unsigned integer: ");
    result = scanf("%u", &value);
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Original value: %u\n", value);
    printf("After setting rightmost unset bit: %u\n", set_rightmost_unset_bit(value));

    return EXIT_SUCCESS;
}