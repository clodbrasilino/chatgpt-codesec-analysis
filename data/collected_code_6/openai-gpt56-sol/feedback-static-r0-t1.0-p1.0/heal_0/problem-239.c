#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_sequences(size_t n, size_t m, uint64_t *result)
{
    uint64_t *counts;
    size_t i;
    size_t length;

    if (result == NULL || n == 0 || m == 0) {
        return 0;
    }

    if (m > (SIZE_MAX / sizeof(*counts)) - 1U) {
        return 0;
    }

    counts = calloc(m + 1U, sizeof(*counts));
    if (counts == NULL) {
        return 0;
    }

    for (i = 1U; i <= m; ++i) {
        counts[i] = 1U;
    }

    for (length = 2U; length <= n; ++length) {
        uint64_t prefix = 0U;

        for (i = 1U; i <= m; ++i) {
            uint64_t next_prefix;
            size_t limit = i / 2U;

            if (UINT64_MAX - prefix < counts[i]) {
                free(counts);
                return 0;
            }

            next_prefix = prefix + counts[i];
            counts[i] = limit == 0U ? 0U : prefix;
            prefix = next_prefix;
        }
    }

    *result = 0U;
    for (i = 1U; i <= m; ++i) {
        if (UINT64_MAX - *result < counts[i]) {
            free(counts);
            return 0;
        }
        *result += counts[i];
    }

    free(counts);
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

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}