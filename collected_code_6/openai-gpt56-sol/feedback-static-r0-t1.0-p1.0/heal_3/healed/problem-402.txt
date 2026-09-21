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
    return (a >= modulus - b) ? a - (modulus - b) : a + b;
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

static int discard_line_remainder(void)
{
    int ch;
    int only_whitespace = 1;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            only_whitespace = 0;
        }
    }

    return only_whitespace;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;

    capacity = 128;
    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';
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

    if (ch == '\n' && !discard_line_remainder()) {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", ncr_mod(n, r, modulus));

    free(input);
    return EXIT_SUCCESS;
}