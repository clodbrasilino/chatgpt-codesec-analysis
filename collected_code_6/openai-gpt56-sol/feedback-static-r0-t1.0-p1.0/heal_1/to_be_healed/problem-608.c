#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int bell_number(size_t n, uint64_t *result)
{
    uint64_t *row;

    if (result == NULL || n > SIZE_MAX / sizeof(*row) - 1U) {
        return -1;
    }

    row = calloc(n + 1U, sizeof(*row));
    if (row == NULL) {
        return -1;
    }

    row[0] = 1U;

    for (size_t i = 1U; i <= n; ++i) {
        row[i] = row[0];

        for (size_t j = i; j > 0U; --j) {
            if (UINT64_MAX - row[j - 1U] < row[j]) {
                free(row);
                return -1;
            }
            row[j - 1U] += row[j];
        }
    }

    *result = row[0];
    free(row);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end;
    uintmax_t value;
    uint64_t result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno != 0 || end == input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
        ++end;
    }

    if (*end != '\0' || value > SIZE_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (bell_number((size_t)value, &result) != 0) {
        fputs("Bell number cannot be represented or computed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}