#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

static bool all_bits_unset_in_range(unsigned int num, unsigned int left, unsigned int right)
{
    unsigned int mask;
    unsigned int width;

    if (left > right) {
        unsigned int tmp = left;
        left = right;
        right = tmp;
    }

    if (left < 1u || right > (unsigned int)(sizeof(unsigned int) * CHAR_BIT)) {
        fprintf(stderr, "Bit range out of bounds\n");
        exit(EXIT_FAILURE);
    }

    width = right - left + 1u;

    if (width >= (unsigned int)(sizeof(unsigned int) * CHAR_BIT)) {
        mask = ~0u;
    } else {
        mask = ((1u << width) - 1u) << (left - 1u);
    }

    return (num & mask) == 0u;
}

int main(void)
{
    unsigned int num = 17u;
    unsigned int left = 2u;
    unsigned int right = 4u;

    if (all_bits_unset_in_range(num, left, right)) {
        printf("All bits are unset in the range %u to %u\n", left, right);
    } else {
        printf("Not all bits are unset in the range %u to %u\n", left, right);
    }

    num = 39u;
    left = 4u;
    right = 5u;

    if (all_bits_unset_in_range(num, left, right)) {
        printf("All bits are unset in the range %u to %u\n", left, right);
    } else {
        printf("Not all bits are unset in the range %u to %u\n", left, right);
    }

    return EXIT_SUCCESS;
}