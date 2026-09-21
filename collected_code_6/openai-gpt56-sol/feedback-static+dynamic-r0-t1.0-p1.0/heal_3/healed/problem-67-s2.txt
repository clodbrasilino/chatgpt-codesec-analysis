#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int bell_number(size_t n, uint64_t *result)
{
    uint64_t *row;

    if (result == NULL || n > SIZE_MAX / sizeof(*row) - 1) {
        return -1;
    }

    row = calloc(n + 1, sizeof(*row));
    if (row == NULL) {
        return -1;
    }

    row[0] = 1;

    for (size_t i = 1; i <= n; ++i) {
        uint64_t previous = row[0];
        row[0] = row[i - 1];

        for (size_t j = 1; j <= i; ++j) {
            uint64_t current = row[j];

            if (previous > UINT64_MAX - row[j - 1]) {
                free(row);
                return -2;
            }

            row[j] = row[j - 1] + previous;
            previous = current;
        }
    }

    *result = row[0];
    free(row);
    return 0;
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    uintmax_t value;
    uint64_t result;
    int status;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (end == input + sizeof input - 1 && input[sizeof input - 2] != '\n') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (value > SIZE_MAX - 1) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    status = bell_number((size_t)value, &result);

    if (status == -1) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == -2) {
        fputs("Bell number exceeds uint64_t range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}