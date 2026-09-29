#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static bool has_subset_sum_divisible_by_m(const long long *values, size_t count, size_t modulus)
{
    bool *reachable = NULL;
    bool *next = NULL;
    size_t i;
    size_t r;

    if (values == NULL || count == 0U || modulus == 0U) {
        return false;
    }

    if (count >= modulus) {
        return true;
    }

    if (modulus > SIZE_MAX / sizeof(*reachable)) {
        return false;
    }

    reachable = calloc(modulus, sizeof(*reachable));
    next = calloc(modulus, sizeof(*next));
    if (reachable == NULL || next == NULL) {
        free(reachable);
        free(next);
        return false;
    }

    for (i = 0U; i < count; ++i) {
        const long long mod = (long long)modulus;
        long long remainder = values[i] % mod;
        bool *temporary;

        if (remainder < 0) {
            remainder += mod;
        }

        for (r = 0U; r < modulus; ++r) {
            next[r] = reachable[r];
        }

        next[(size_t)remainder] = true;

        for (r = 0U; r < modulus; ++r) {
            if (reachable[r]) {
                size_t combined;

                if (r >= modulus - (size_t)remainder) {
                    combined = r - (modulus - (size_t)remainder);
                } else {
                    combined = r + (size_t)remainder;
                }
                next[combined] = true;
            }
        }

        temporary = reachable;
        reachable = next;
        next = temporary;

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
    long long *values = NULL;
    size_t i;
    bool result;

    if (scanf("%zu %zu", &count, &modulus) != 2 || count == 0U ||
        /* Possible weaknesses found:
         *  use of undeclared identifier 'LLONG_MAX'
         *  'LLONG_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        modulus == 0U || modulus > (size_t)LLONG_MAX ||
        count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%lld", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    result = has_subset_sum_divisible_by_m(values, count, modulus);
    free(values);

    if (printf("%s\n", result ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}