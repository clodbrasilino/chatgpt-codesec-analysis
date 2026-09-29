#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int entringer_number(size_t n, size_t k, uint64_t *result)
{
    uint64_t *row;

    if (result == NULL || k > n || n == SIZE_MAX) {
        return -1;
    }

    row = calloc(n + 1, sizeof(*row));
    if (row == NULL) {
        return -1;
    }

    row[0] = UINT64_C(1);

    for (size_t i = 1; i <= n; ++i) {
        uint64_t previous = row[0];

        row[0] = 0;

        for (size_t j = 1; j <= i; ++j) {
            uint64_t old = row[j];

            if (UINT64_MAX - row[j - 1] < previous) {
                free(row);
                return -1;
            }

            row[j] = row[j - 1] + previous;
            previous = old;
        }
    }

    *result = row[k];
    free(row);
    return 0;
}

int main(int argc, char const * const argv[])
{
    char *end;
    uintmax_t n_input;
    uintmax_t k_input;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n k\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    n_input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        n_input > SIZE_MAX - 1) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    k_input = strtoumax(argv[2], &end, 10);

    if (errno != 0 || end == argv[2] || *end != '\0' ||
        k_input > SIZE_MAX || k_input > n_input) {
        fprintf(stderr, "Invalid k\n");
        return EXIT_FAILURE;
    }

    if (entringer_number((size_t)n_input, (size_t)k_input, &result) != 0) {
        fprintf(stderr, "Unable to compute the Entringer number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}