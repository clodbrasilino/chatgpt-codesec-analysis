#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                                uint64_t n, unsigned int *digit)
{
    uint64_t remainder;

    if (denominator == 0 || n == 0 || digit == NULL) {
        return 0;
    }

    remainder = numerator % denominator;

    for (uint64_t i = 1; i < n; ++i) {
        remainder = (uint64_t)(((__uint128_t)remainder * 10U) % denominator);
    }

    *digit = (unsigned int)(((__uint128_t)remainder * 10U) / denominator);
    return 1;
}

static int is_space_character(char character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

static int parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (is_space_character(**input)) {
        ++*input;
    }

    if (**input == '\0' || **input == '-' || **input == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    ssize_t length;
    const char *input;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t n;
    unsigned int digit;

    length = getline(&buffer, &capacity, stdin);
    if (length < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    input = buffer;

    if (!parse_uint64(&input, &numerator) ||
        !parse_uint64(&input, &denominator) ||
        !parse_uint64(&input, &n)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    while (is_space_character(*input)) {
        ++input;
    }

    if (*input != '\0') {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (!nth_fractional_digit(numerator, denominator, n, &digit)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}