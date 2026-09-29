#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int entringer_number(size_t n, size_t k, uint64_t *result)
{
    uint64_t *row = NULL;

    if (result == NULL || k > n) {
        return EINVAL;
    }

    if (n == SIZE_MAX || n + 1U > SIZE_MAX / sizeof(*row)) {
        return EOVERFLOW;
    }

    row = calloc(n + 1U, sizeof(*row));
    if (row == NULL) {
        return ENOMEM;
    }

    row[0] = 1U;

    for (size_t i = 1U; i <= n; ++i) {
        uint64_t previous = 0U;

        for (size_t j = 1U; j <= i; ++j) {
            uint64_t old = row[j];

            if (UINT64_MAX - row[j - 1U] < previous) {
                free(row);
                return ERANGE;
            }

            row[j] = previous + row[j - 1U];
            previous = old;
        }

        row[0] = 0U;
    }

    *result = row[k];
    free(row);
    return 0;
}

int main(void)
{
    size_t n = 0U;
    size_t k = 0U;
    uint64_t result = 0U;
    int status;

    if (scanf("%zu %zu", &n, &k) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = entringer_number(n, k, &result);
    if (status != 0) {
        errno = status;
        perror("entringer_number");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}