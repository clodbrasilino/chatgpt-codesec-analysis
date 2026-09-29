#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t p)
{
    return a >= p - b ? a - (p - b) : a + b;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t p, int *error)
{
    uint64_t *values;
    uint64_t i;
    uint64_t j;
    uint64_t result;
    size_t count;

    *error = 0;

    if (p == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*values) - 1U)) {
        *error = ENOMEM;
        return 0;
    }

    count = (size_t)r + 1U;
    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        *error = ENOMEM;
        return 0;
    }

    values[0] = 1U % p;

    for (i = 1; i <= n; ++i) {
        uint64_t limit = i < r ? i : r;

        for (j = limit; j > 0; --j) {
            values[j] = add_mod(values[j], values[j - 1U], p);
        }

        if (i == UINT64_MAX) {
            break;
        }
    }

    result = values[r];
    free(values);
    return result;
}

int main(void)
{
    char input[256];
    char *cursor;
    char *end;
    uint64_t values[3];
    uint64_t result;
    int error;
    size_t i;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    for (i = 0; i < 3; ++i) {
        while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' ||
               *cursor == '\f' || *cursor == '\v') {
            ++cursor;
        }

        if (*cursor == '\0' || *cursor == '\n' || *cursor == '-') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        errno = 0;
        values[i] = strtoumax(cursor, &end, 10);

        if (end == cursor || errno == ERANGE) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        cursor = end;
    }

    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' ||
           *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    if (*cursor != '\0' && *cursor != '\n') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (values[2] == 0) {
        fputs("Modulus must be nonzero\n", stderr);
        return EXIT_FAILURE;
    }

    result = ncr_mod(values[0], values[1], values[2], &error);
    if (error != 0) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}