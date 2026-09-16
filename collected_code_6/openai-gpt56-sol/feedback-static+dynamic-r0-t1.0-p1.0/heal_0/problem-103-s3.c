#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int eulerian_number(size_t n, size_t m, uint64_t *result)
{
    uint64_t *values;
    size_t count;
    size_t i;
    size_t j;

    if (result == NULL) {
        return EINVAL;
    }

    if (n == 0U) {
        *result = (m == 0U) ? 1U : 0U;
        return 0;
    }

    if (m >= n) {
        *result = 0U;
        return 0;
    }

    if (m == 0U) {
        *result = 1U;
        return 0;
    }

    if (m > (SIZE_MAX / sizeof(*values)) - 1U) {
        return ENOMEM;
    }

    count = m + 1U;
    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        return ENOMEM;
    }

    values[0] = 1U;

    for (i = 1U; i <= n; ++i) {
        size_t upper = (i - 1U < m) ? i - 1U : m;

        for (j = upper; j > 0U; --j) {
            uint64_t left_factor = (uint64_t)(i - j);
            uint64_t right_factor = (uint64_t)(j + 1U);
            uint64_t left;
            uint64_t right;

            if (values[j - 1U] > UINT64_MAX / left_factor) {
                free(values);
                return ERANGE;
            }
            left = values[j - 1U] * left_factor;

            if (values[j] > UINT64_MAX / right_factor) {
                free(values);
                return ERANGE;
            }
            right = values[j] * right_factor;

            if (left > UINT64_MAX - right) {
                free(values);
                return ERANGE;
            }

            values[j] = left + right;
        }
    }

    *result = values[m];
    free(values);
    return 0;
}

int main(void)
{
    size_t n;
    size_t m;
    uint64_t result;
    int status;

    if (scanf("%zu %zu", &n, &m) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = eulerian_number(n, m, &result);
    if (status == ENOMEM) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }
    if (status == ERANGE) {
        fputs("Result exceeds uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }
    if (status != 0) {
        fputs("Unable to compute Eulerian number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}