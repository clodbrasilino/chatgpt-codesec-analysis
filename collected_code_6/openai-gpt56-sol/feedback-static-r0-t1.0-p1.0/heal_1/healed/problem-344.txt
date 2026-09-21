#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t result = 0;
    uint64_t bit = UINT64_C(1) << 62;

    while (bit > value) {
        bit >>= 2;
    }

    while (bit != 0) {
        if (value >= result + bit) {
            value -= result + bit;
            result = (result >> 1) + bit;
        } else {
            result >>= 1;
        }

        bit >>= 2;
    }

    return result;
}

static uint64_t count_odd_factors_in_range(uint64_t lower, uint64_t upper)
{
    uint64_t count;
    uint64_t squares;

    if (lower > upper) {
        return 0;
    }

    count = upper - lower + UINT64_C(1);
    squares = integer_sqrt(upper);

    if (lower != 0) {
        squares -= integer_sqrt(lower - UINT64_C(1));
    }

    return count - squares;
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

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    char buffer[256];
    const char *input;
    uint64_t lower;
    uint64_t upper;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 1;
    }

    input = buffer;

    if (!parse_uint64(&input, &lower) || !parse_uint64(&input, &upper)) {
        return 1;
    }

    while (*input == ' ' || *input == '\t' ||
           *input == '\n' || *input == '\r' ||
           *input == '\f' || *input == '\v') {
        ++input;
    }

    if (*input != '\0' || lower > upper) {
        return 1;
    }

    printf("%" PRIu64 "\n", count_odd_factors_in_range(lower, upper));
    return 0;
}