#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int bell_number(size_t n, uint64_t *result)
{
    if (result == NULL || n == SIZE_MAX ||
        n + 1 > SIZE_MAX / sizeof(uint64_t)) {
        return 0;
    }

    uint64_t *row = calloc(n + 1, sizeof(*row));
    if (row == NULL) {
        return 0;
    }

    row[0] = 1;

    for (size_t i = 1; i <= n; ++i) {
        uint64_t previous = row[0];
        row[0] = row[i - 1];

        for (size_t j = 1; j <= i; ++j) {
            uint64_t current = row[j];

            if (previous > UINT64_MAX - row[j - 1]) {
                free(row);
                return 0;
            }

            row[j] = row[j - 1] + previous;
            previous = current;
        }
    }

    *result = row[0];
    free(row);
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <set-size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input > (uintmax_t)SIZE_MAX) {
        fprintf(stderr, "Invalid set size\n");
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!bell_number((size_t)input, &result)) {
        fprintf(stderr, "Unable to compute the Bell number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}