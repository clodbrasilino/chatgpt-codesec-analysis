#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_sequences(size_t n, size_t m, uint64_t *result)
{
    uint64_t *current;
    uint64_t *next;

    if (result == NULL || n == 0U || m == 0U) {
        return 0;
    }

    if (m > (SIZE_MAX / sizeof(*current)) - 1U) {
        return 0;
    }

    current = calloc(m + 1U, sizeof(*current));
    next = calloc(m + 1U, sizeof(*next));
    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        return 0;
    }

    for (size_t value = 1U; value <= m; ++value) {
        current[value] = 1U;
    }

    for (size_t length = 2U; length <= n; ++length) {
        uint64_t prefix = 0U;

        for (size_t value = 1U; value <= m; ++value) {
            if (UINT64_MAX - prefix < current[value]) {
                free(current);
                free(next);
                return 0;
            }

            prefix += current[value];

            if (value <= m / 2U) {
                next[value * 2U] = prefix;
                if (value * 2U < m) {
                    next[value * 2U + 1U] = prefix;
                }
            }
        }

        uint64_t *temporary = current;
        current = next;
        next = temporary;

        for (size_t value = 1U; value <= m; ++value) {
            next[value] = 0U;
        }
    }

    *result = 0U;
    for (size_t value = 1U; value <= m; ++value) {
        if (UINT64_MAX - *result < current[value]) {
            free(current);
            free(next);
            return 0;
        }
        *result += current[value];
    }

    free(current);
    free(next);
    return 1;
}

int main(void)
{
    size_t n;
    size_t m;
    uint64_t result;

    errno = 0;
    if (scanf("%zu %zu", &n, &m) != 2 || errno != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_sequences(n, m, &result)) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}