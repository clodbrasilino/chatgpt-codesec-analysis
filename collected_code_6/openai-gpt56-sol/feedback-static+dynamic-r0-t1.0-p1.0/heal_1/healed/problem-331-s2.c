#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_unset_bits(unsigned int value)
{
    unsigned int count = 0U;

    do {
        if ((value & 1U) == 0U) {
            ++count;
        }
        value >>= 1U;
    } while (value != 0U);

    return count;
}

int main(void)
{
    unsigned int value;

    if (scanf("%u", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%u\n", count_unset_bits(value));
    return EXIT_SUCCESS;
}