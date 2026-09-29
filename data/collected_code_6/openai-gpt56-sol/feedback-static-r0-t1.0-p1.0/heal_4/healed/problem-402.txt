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
    const char *p = *cursor;
    char *end = NULL;
    uintmax_t parsed;

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
    size_t capacity = 128;
    char *line = malloc(capacity);
    int ch;

    if (line == NULL) {
        return 0;
    }

    *length = 0;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (*length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (*length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[(*length)++] = (char)ch;
    }

    if (ch == EOF && *length == 0) {
        free(line);
        return 0;
    }

    line[*length] = '\0';
    *buffer = line;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;

    if (!read_line(&input, &length)) {
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_u64(&cursor, &n) ||
        !parse_u64(&cursor, &r) ||
        !parse_u64(&cursor, &modulus)) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || modulus == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", ncr_mod(n, r, modulus)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}