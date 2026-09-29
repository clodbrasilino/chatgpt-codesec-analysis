#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static size_t count_odd_set_bits(const unsigned int values[], size_t count)
{
    size_t result = 0U;

    if (values == NULL && count != 0U) {
        return 0U;
    }

    for (size_t i = 0U; i < count; ++i) {
        unsigned int value = values[i];
        unsigned int parity = 0U;

        while (value != 0U) {
            parity ^= 1U;
            value &= value - 1U;
        }

        if (parity != 0U) {
            ++result;
        }
    }

    return result;
}

int main(void)
{
    unsigned int values[] = {1U, 2U, 3U, 7U, 8U, UINT_MAX};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t result = count_odd_set_bits(values, count);

    if (printf("%zu\n", result) < 0) {
        return 1;
    }

    return 0;
}