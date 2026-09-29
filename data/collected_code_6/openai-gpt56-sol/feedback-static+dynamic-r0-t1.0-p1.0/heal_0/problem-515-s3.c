#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool has_subset_sum_divisible_by_m(const long long *values, size_t count,
                                           size_t modulus)
{
    bool *reachable = NULL;
    bool *next = NULL;
    size_t i;
    size_t remainder;

    if (values == NULL || count == 0 || modulus == 0) {
        return false;
    }

    if (count >= modulus) {
        return true;
    }

    reachable = calloc(modulus, sizeof(*reachable));
    next = calloc(modulus, sizeof(*next));

    if (reachable == NULL || next == NULL) {
        free(reachable);
        free(next);
        return false;
    }

    for (i = 0; i < count; ++i) {
        long long normalized = values[i] % (long long)modulus;
        size_t value_remainder;

        if (normalized < 0) {
            normalized += (long long)modulus;
        }

        value_remainder = (size_t)normalized;

        for (remainder = 0; remainder < modulus; ++remainder) {
            next[remainder] = reachable[remainder];
        }

        next[value_remainder] = true;

        for (remainder = 0; remainder < modulus; ++remainder) {
            if (reachable[remainder]) {
                size_t combined;

                if (remainder >= modulus - value_remainder) {
                    combined = remainder - (modulus - value_remainder);
                } else {
                    combined = remainder + value_remainder;
                }

                next[combined] = true;
            }
        }

        if (next[0]) {
            free(reachable);
            free(next);
            return true;
        }

        {
            bool *temporary = reachable;
            reachable = next;
            next = temporary;
        }
    }

    free(reachable);
    free(next);
    return false;
}

int main(void)
{
    long long values[] = {3, 1, 7, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t modulus = 6;
    const bool found = has_subset_sum_divisible_by_m(values, count, modulus);

    if (printf("%s\n", found ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}