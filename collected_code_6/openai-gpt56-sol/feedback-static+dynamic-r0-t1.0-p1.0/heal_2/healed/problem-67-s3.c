#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int bell_number(size_t n, uint64_t *result)
{
    if (result == NULL || n == SIZE_MAX) {
        return -1;
    }

    uint64_t *row = calloc(n + 1, sizeof *row);
    if (row == NULL) {
        return -1;
    }

    row[0] = 1;

    for (size_t i = 1; i <= n; ++i) {
        uint64_t previous = row[0];
        row[0] = row[i - 1];

        for (size_t j = 1; j <= i; ++j) {
            uint64_t upper_left = previous;
            previous = row[j];

            if (UINT64_MAX - row[j - 1] < upper_left) {
                free(row);
                return -1;
            }

            row[j] = row[j - 1] + upper_left;
        }
    }

    *result = row[0];
    free(row);
    return 0;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <set-size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > SIZE_MAX) {
        fprintf(stderr, "Invalid set size\n");
        return EXIT_FAILURE;
    }

    uint64_t result;
    if (bell_number((size_t)input, &result) != 0) {
        fprintf(stderr,
                "Unable to compute Bell number due to overflow or allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}