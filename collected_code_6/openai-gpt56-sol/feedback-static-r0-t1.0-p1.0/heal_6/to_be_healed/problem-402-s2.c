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
    uint64_t i;
    uint64_t j;
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

    for (i = 1; i <= n; ++i) {
        uint64_t limit = i < r ? i : r;

        for (j = limit; j != 0; --j) {
            row[j] = add_mod(row[j], row[j - 1U], modulus);
        }

        if (i == UINT64_MAX) {
            break;
        }
    }

    result = row[r];
    free(row);
    return result;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[32];
    size_t length = 0;
    char *end;
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ||
             ch == '\f' || ch == '\v');

    if (ch == '-') {
        return 0;
    }

    do {
        if (length + 1U >= sizeof(token)) {
            return 0;
        }

        token[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && ch != ' ' && ch != '\t' && ch != '\n' &&
             ch != '\r' && ch != '\f' && ch != '\v');

    token[length] = '\0';

    if (ch != EOF && ungetc(ch, stdin) == EOF) {
        return 0;
    }

    errno = 0;
    *value = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0') {
        return 0;
    }

    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' &&
            ch != '\f' && ch != '\v') {
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