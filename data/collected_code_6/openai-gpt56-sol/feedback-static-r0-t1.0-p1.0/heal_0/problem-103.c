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

    if (m > (SIZE_MAX / sizeof(*values)) - 1U) {
        return EOVERFLOW;
    }

    count = m + 1U;
    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        return ENOMEM;
    }

    values[0] = 1U;

    for (i = 1U; i <= n; ++i) {
        size_t upper = (m < i - 1U) ? m : i - 1U;

        for (j = upper + 1U; j-- > 0U;) {
            uint64_t left = values[j];
            uint64_t right = (j > 0U) ? values[j - 1U] : 0U;
            size_t left_factor = j + 1U;
            size_t right_factor = i - j;
            uint64_t left_term;
            uint64_t right_term;

            if (left_factor > UINT64_MAX || right_factor > UINT64_MAX) {
                free(values);
                return EOVERFLOW;
            }

            if (left != 0U && left_factor > UINT64_MAX / left) {
                free(values);
                return EOVERFLOW;
            }

            if (right != 0U && right_factor > UINT64_MAX / right) {
                free(values);
                return EOVERFLOW;
            }

            left_term = left * (uint64_t)left_factor;
            right_term = right * (uint64_t)right_factor;

            if (left_term > UINT64_MAX - right_term) {
                free(values);
                return EOVERFLOW;
            }

            values[j] = left_term + right_term;
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
    if (status != 0) {
        if (status == EOVERFLOW) {
            fputs("Result exceeds uint64_t range\n", stderr);
        } else if (status == ENOMEM) {
            fputs("Memory allocation failed\n", stderr);
        } else {
            fputs("Invalid argument\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}