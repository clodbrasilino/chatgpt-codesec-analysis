#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                         uint64_t n, unsigned int *digit)
{
    uint64_t remainder;
    uint64_t i;

    if (denominator == 0 || n == 0 || digit == NULL) {
        return 0;
    }

    remainder = numerator % denominator;

    for (i = 1; i < n; ++i) {
        remainder = (uint64_t)(((__uint128_t)remainder * 10U) % denominator);
    }

    *digit = (unsigned int)(((__uint128_t)remainder * 10U) / denominator);
    return 1;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    while (**input == ' ' || **input == '\t' ||
           **input == '\n' || **input == '\r' ||
           **input == '\f' || **input == '\v') {
        ++*input;
    }

    if (**input == '\0' || **input == '-' || **input == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (errno == ERANGE || end == *input || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    const char *input;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t n;
    unsigned int digit;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 1;
    }

    input = buffer;

    if (!parse_uint64(&input, &numerator) ||
        !parse_uint64(&input, &denominator) ||
        !parse_uint64(&input, &n)) {
        return 1;
    }

    while (*input == ' ' || *input == '\t' ||
           *input == '\n' || *input == '\r' ||
           *input == '\f' || *input == '\v') {
        ++input;
    }

    if (*input != '\0') {
        return 1;
    }

    if (!nth_fractional_digit(numerator, denominator, n, &digit)) {
        return 1;
    }

    if (printf("%u\n", digit) < 0) {
        return 1;
    }

    return 0;
}