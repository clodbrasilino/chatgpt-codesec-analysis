#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int bell_number(size_t n, uint64_t *result)
{
    uint64_t *row = NULL;

    if (result == NULL) {
        return EINVAL;
    }

    if (n > SIZE_MAX / sizeof(*row) - 1U) {
        return EOVERFLOW;
    }

    row = calloc(n + 1U, sizeof(*row));
    if (row == NULL) {
        return ENOMEM;
    }

    row[0] = 1U;

    for (size_t i = 1U; i <= n; ++i) {
        uint64_t diagonal = row[0];
        row[0] = row[i - 1U];

        for (size_t j = 1U; j <= i; ++j) {
            uint64_t previous = row[j];

            if (UINT64_MAX - row[j - 1U] < diagonal) {
                free(row);
                return ERANGE;
            }

            row[j] = row[j - 1U] + diagonal;
            diagonal = previous;
        }
    }

    *result = row[0];
    free(row);
    return 0;
}

int main(void)
{
    size_t n = 0U;
    uint64_t result = 0U;
    int status = 0;

    if (scanf("%zu", &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = bell_number(n, &result);
    if (status == ENOMEM) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }
    if (status == EOVERFLOW || status == ERANGE) {
        fputs("Bell number cannot be represented\n", stderr);
        return EXIT_FAILURE;
    }
    if (status != 0) {
        fputs("Unable to compute Bell number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}