#include <stdio.h>
#include <stdlib.h>

unsigned int set_leftmost_unset_bit(unsigned int n)
{
    unsigned int pos;
    unsigned int temp;

    if (n == 0U) {
        return 1U;
    }

    if ((n & (n + 1U)) == 0U) {
        return n;
    }

    pos = 0U;
    temp = n;
    while (temp > 1U) {
        temp >>= 1U;
        pos++;
    }

    while (pos > 0U) {
        if ((n & (1U << pos)) == 0U) {
            return n | (1U << pos);
        }
        pos--;
    }

    return n;
}

int main(void)
{
    unsigned int values[] = { 10U, 15U, 0U, 21U, 7U };
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        unsigned int result = set_leftmost_unset_bit(values[i]);
        if (printf("Input: %u, Output: %u\n", values[i], result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}