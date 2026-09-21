#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static size_t count_odd_set_bits(const uint64_t *values, size_t count)
{
    size_t odd_count = 0U;

    if (values == NULL && count != 0U) {
        return 0U;
    }

    for (size_t i = 0U; i < count; ++i) {
        uint64_t value = values[i];
        unsigned int parity = 0U;

        while (value != 0U) {
            parity ^= 1U;
            value &= value - UINT64_C(1);
        }

        if (parity != 0U) {
            ++odd_count;
        }
    }

    return odd_count;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    size_t odd_count = 0U;

    for (size_t i = 0U; i < count; ++i) {
        uint64_t value = 0U;

        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNu64, &value) != 1) {
            fputs("Invalid input\n", stderr);
            return 1;
        }

        odd_count += count_odd_set_bits(&value, 1U);
    }

    if (printf("%zu\n", odd_count) < 0) {
        return 1;
    }

    return 0;
}