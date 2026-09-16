#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int eulerian_number(size_t n, size_t m, uint64_t *result)
{
    uint64_t *values;

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

    values = calloc(m + 1U, sizeof(*values));
    if (values == NULL) {
        return ENOMEM;
    }

    values[0] = 1U;

    for (size_t i = 1U; i <= n; ++i) {
        size_t upper = (i - 1U < m) ? i - 1U : m;

        for (size_t j = upper + 1U; j-- > 0U;) {
            uint64_t left = 0U;
            uint64_t right = 0U;
            uint64_t left_factor = j + 1U;
            uint64_t right_factor = i - j;

            if (values[j] > UINT64_MAX / left_factor) {
                free(values);
                return ERANGE;
            }
            left = left_factor * values[j];

            if (j > 0U) {
                if (values[j - 1U] > UINT64_MAX / right_factor) {
                    free(values);
                    return ERANGE;
                }
                right = right_factor * values[j - 1U];
            }

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
    if (status != 0) {
        errno = status;
        perror("Unable to compute Eulerian number");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}