#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    a %= modulus;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus)
{
    uint64_t result = 1;

    if (modulus == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (uint64_t i = 1; i <= r; ++i) {
        uint64_t numerator = n - r + i;
        uint64_t denominator = i;
        uint64_t divisor = gcd_u64(numerator, denominator);

        numerator /= divisor;
        denominator /= divisor;

        divisor = gcd_u64(result, denominator);
        result /= divisor;
        denominator /= divisor;

        if (denominator != 1) {
            uint64_t j = i + 1;

            while (denominator != 1 && j <= r) {
                uint64_t future = n - r + j;

                divisor = gcd_u64(future, denominator);
                denominator /= divisor;
                ++j;
            }

            if (denominator != 1) {
                return 0;
            }
        }

        result = multiply_mod(result, numerator % modulus, modulus);
    }

    return result;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    const char *p;
    char *end = NULL;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = *cursor;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-' || *p == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(p, &end, 10);

    if (end == p || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

static int read_line(char **buffer, size_t *length)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *line;
    size_t used = 0;
    int ch;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    line = malloc((size_t)MAX_INPUT_LENGTH + 1);
    if (line == NULL) {
        return 0;
    }

    while (used < MAX_INPUT_LENGTH) {
        ch = fgetc(stdin);

        if (ch == '\n') {
            line[used] = '\0';
            *buffer = line;
            *length = used;
            return 1;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0) {
                free(line);
                return 0;
            }

            line[used] = '\0';
            *buffer = line;
            *length = used;
            return 1;
        }

        line[used++] = (char)ch;
    }

    ch = fgetc(stdin);
    if (ch != '\n' && ch != EOF) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);
    }

    free(line);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    int status = EXIT_FAILURE;

    if (!read_line(&input, &length)) {
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_u64(&cursor, &n) ||
        !parse_u64(&cursor, &r) ||
        !parse_u64(&cursor, &modulus)) {
        goto cleanup;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || modulus == 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", ncr_mod(n, r, modulus)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}