#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int entringer_number(size_t n, size_t k, uint64_t *result)
{
    uint64_t *row;
    size_t bytes;

    if (result == NULL || k > n) {
        return 0;
    }

    if (n == SIZE_MAX || n + 1 > SIZE_MAX / sizeof(*row)) {
        return 0;
    }

    bytes = (n + 1) * sizeof(*row);
    row = calloc(1, bytes);
    if (row == NULL) {
        return 0;
    }

    row[0] = 1;

    for (size_t i = 1; i <= n; ++i) {
        uint64_t previous = 0;

        for (size_t j = 1; j <= i; ++j) {
            uint64_t old_value = row[j];

            if (UINT64_MAX - previous < row[j - 1]) {
                free(row);
                return 0;
            }

            row[j] = previous + row[j - 1];
            previous = old_value;
        }

        row[0] = 0;
    }

    *result = row[k];
    free(row);
    return 1;
}

int main(void)
{
    size_t n;
    size_t k;
    uint64_t result;

    if (scanf("%zu %zu", &n, &k) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!entringer_number(n, k, &result)) {
        fputs("Unable to compute Entringer number\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}