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
    uint64_t *row;
    uint64_t result;
    size_t count;

    *error = 0;

    if (modulus == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*row) - 1U)) {
        *error = ENOMEM;
        return 0;
    }

    count = (size_t)r + 1U;
    row = calloc(count, sizeof(*row));
    if (row == NULL) {
        *error = ENOMEM;
        return 0;
    }

    row[0] = 1U % modulus;

    for (uint64_t i = 1;; ++i) {
        uint64_t limit = i < r ? i : r;

        for (uint64_t j = limit; j != 0; --j) {
            row[j] = add_mod(row[j], row[j - 1U], modulus);
        }

        if (i == n) {
            break;
        }
    }

    result = row[r];
    free(row);
    return result;
}

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    char *end;
    int ch;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (is_space_char(ch));

    if (ch == '-') {
        return 0;
    }

    if (ungetc(ch, stdin) == EOF) {
        return 0;
    }

    errno = 0;
    if (fscanf(stdin, "%" SCNuMAX, &parsed) != 1) {
        return 0;
    }

    if (errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    ch = fgetc(stdin);
    if (ch != EOF && !is_space_char(ch)) {
        return 0;
    }

    if (ch != EOF && ungetc(ch, stdin) == EOF) {
        return 0;
    }

    end = NULL;
    (void)end;
    *value = (uint64_t)parsed;
    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (!is_space_char(ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;
    int error;

    if (!read_uint64(&n) ||
        !read_uint64(&r) ||
        !read_uint64(&modulus) ||
        !only_whitespace_remains()) {
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