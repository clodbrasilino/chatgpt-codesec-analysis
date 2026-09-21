#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    uint64_t bits = (uint64_t)value;
    return value < 0 ? UINT64_C(0) - bits : bits;
}

static int multiply_int64(int64_t left, int64_t right, int64_t *result)
{
    uint64_t multiplicand;
    uint64_t multiplier;
    uint64_t product = 0;
    uint64_t limit;
    int negative;

    if (result == NULL) {
        return 0;
    }

    negative = (left < 0) != (right < 0);
    multiplicand = magnitude(left);
    multiplier = magnitude(right);
    limit = negative ? (UINT64_C(1) << 63) : (uint64_t)INT64_MAX;

    while (multiplier != 0) {
        if ((multiplier & UINT64_C(1)) != 0) {
            if (multiplicand > limit - product) {
                return 0;
            }
            product += multiplicand;
        }

        multiplier >>= 1;

        if (multiplier != 0) {
            if (multiplicand > limit - multiplicand) {
                return 0;
            }
            multiplicand += multiplicand;
        }
    }

    if (negative) {
        *result = product == (UINT64_C(1) << 63)
                      ? INT64_MIN
                      : -(int64_t)product;
    } else {
        *result = (int64_t)product;
    }

    return 1;
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;
    intmax_t parsed;

    while (**input == ' ' || **input == '\t' ||
           **input == '\n' || **input == '\r' ||
           **input == '\f' || **input == '\v') {
        ++*input;
    }

    errno = 0;
    parsed = strtoimax(*input, &end, 10);

    if (end == *input || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    int64_t left;
    int64_t right;
    int64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &left) || !parse_int64(&cursor, &right)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\n' || *cursor == '\r' ||
           *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!multiply_int64(left, right, &result)) {
        fputs("Multiplication overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}