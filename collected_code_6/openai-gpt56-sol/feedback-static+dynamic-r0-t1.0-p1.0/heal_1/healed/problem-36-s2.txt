#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                                uint64_t position, unsigned int *digit)
{
    uint64_t remainder;

    if (denominator == 0 || position == 0 || digit == NULL) {
        return 0;
    }

    remainder = numerator % denominator;

    for (uint64_t i = 0; i < position; ++i) {
        unsigned int quotient_digit = 0;

        for (unsigned int bit = 0; bit < 4; ++bit) {
            quotient_digit <<= 1;

            if (remainder >= denominator - remainder) {
                remainder = remainder - (denominator - remainder);
                ++quotient_digit;
            } else {
                remainder += remainder;
            }
        }

        if (quotient_digit >= 10) {
            quotient_digit -= 10;
            remainder -= denominator;
        }

        *digit = quotient_digit;
    }

    return 1;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    while (**cursor == ' ' || **cursor == '\t' ||
           **cursor == '\n' || **cursor == '\r' ||
           **cursor == '\f' || **cursor == '\v') {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &numerator) ||
        !parse_uint64(&cursor, &denominator) ||
        !parse_uint64(&cursor, &position)) {
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

    if (!nth_fractional_digit(numerator, denominator, position, &digit)) {
        fputs("Unable to calculate digit\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%u\n", digit);
    return EXIT_SUCCESS;
}