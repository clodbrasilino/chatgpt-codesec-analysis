#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int n)
{
    unsigned int mask;

    if (n <= 2U) {
        return n;
    }

    mask = n;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;

    mask = (mask >> 1) & ~1U;

    return n ^ mask;
}

int main(void)
{
    unsigned int values[] = { 0U, 1U, 2U, 3U, 10U, 15U, 73U, 255U };
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        unsigned int result = toggle_middle_bits(values[i]);
        if (printf("Input: %u -> Output: %u\n", values[i], result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}