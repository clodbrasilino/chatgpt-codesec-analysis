#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

static bool has_subset_sum_divisible_by_m(const long long *values,
                                          size_t count,
                                          size_t modulus)
{
    bool *reachable;
    bool *next;
    const long long signed_modulus = (long long)modulus;

    if (values == NULL || count == 0U || modulus == 0U ||
        modulus > (size_t)LLONG_MAX) {
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

    for (size_t i = 0U; i < count; ++i) {
        long long remainder = values[i] % signed_modulus;

        if (remainder < 0) {
            remainder += signed_modulus;
        }

        for (size_t r = 0U; r < modulus; ++r) {
            next[r] = reachable[r];
        }

        next[(size_t)remainder] = true;

        for (size_t r = 0U; r < modulus; ++r) {
            if (reachable[r]) {
                const size_t rem = (size_t)remainder;
                size_t combined;

                if (r >= modulus - rem) {
                    combined = r - (modulus - rem);
                } else {
                    combined = r + rem;
                }

                next[combined] = true;
            }
        }

        {
            bool *temporary = reachable;
            reachable = next;
            next = temporary;
        }

        if (reachable[0]) {
            free(reachable);
            free(next);
            return true;
        }
    }

    free(reachable);
    free(next);
    return false;
}

int main(void)
{
    size_t count;
    size_t modulus;
    long long *values;

    if (scanf("%zu %zu", &count, &modulus) != 2 ||
        count == 0U ||
        modulus == 0U ||
        modulus > (size_t)LLONG_MAX ||
        count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lld", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%s\n",
           has_subset_sum_divisible_by_m(values, count, modulus)
               ? "Yes"
               : "No");

    free(values);
    return EXIT_SUCCESS;
}