#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus, int *error)
{
    uint64_t *values;
    uint64_t result;
    uint64_t i;
    uint64_t j;
    size_t count;

    *error = 0;

    if (modulus == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r >= SIZE_MAX / sizeof(*values)) {
        *error = ENOMEM;
        return 0;
    }

    count = (size_t)r + 1;
    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        *error = ENOMEM;
        return 0;
    }

    values[0] = 1 % modulus;

    for (i = 1; i <= n; ++i) {
        uint64_t limit = i < r ? i : r;

        for (j = limit; j > 0; --j) {
            values[j] = add_mod(values[j], values[j - 1], modulus);
        }

        if (i == UINT64_MAX) {
            break;
        }
    }

    result = values[r];
    free(values);
    return result;
}

static int parse_uint64(const char **text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)**text)) {
        ++*text;
    }

    if (**text == '\0' || **text == '-' || **text == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*text, &end, 10);

    if (end == *text || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *text = end;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;
    int error;

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

    if (!parse_uint64(&cursor, &n) ||
        !parse_uint64(&cursor, &r) ||
        !parse_uint64(&cursor, &modulus)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (modulus == 0) {
        fputs("Modulus must be nonzero\n", stderr);
        return EXIT_FAILURE;
    }

    result = ncr_mod(n, r, modulus, &error);
    if (error != 0) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}