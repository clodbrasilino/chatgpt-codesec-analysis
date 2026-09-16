#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static size_t count_numbers_with_bits_set(const uint64_t *numbers,
                                          size_t count,
                                          unsigned int oth,
                                          unsigned int nth)
{
    size_t matches = 0U;

    if (numbers == NULL || oth >= 64U || nth >= 64U) {
        return 0U;
    }

    const uint64_t mask = (UINT64_C(1) << oth) | (UINT64_C(1) << nth);

    for (size_t i = 0U; i < count; ++i) {
        if ((numbers[i] & mask) == mask) {
            ++matches;
        }
    }

    return matches;
}

int main(void)
{
    const uint64_t numbers[] = {
        UINT64_C(3),
        UINT64_C(5),
        UINT64_C(7),
        UINT64_C(10),
        UINT64_C(15)
    };
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    const unsigned int oth = 0U;
    const unsigned int nth = 2U;
    const size_t result =
        count_numbers_with_bits_set(numbers, count, oth, nth);

    if (printf("%zu\n", result) < 0) {
        return 1;
    }

    return 0;
}