#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_unset_bits(unsigned int value)
{
    unsigned int count = 0U;

    while (value != 0U) {
        if ((value & 1U) == 0U) {
            ++count;
        }
        value >>= 1U;
    }

    return count;
}

int main(void)
{
    unsigned int value;

    if (scanf("%u", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", count_unset_bits(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}