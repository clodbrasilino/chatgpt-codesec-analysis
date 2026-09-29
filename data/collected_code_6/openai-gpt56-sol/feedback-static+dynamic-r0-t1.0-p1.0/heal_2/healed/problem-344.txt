#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    uint64_t square_count;

    if (lower > upper) {
        return 0;
    }

    count = upper - lower + UINT64_C(1);
    square_count = integer_sqrt(upper);

    if (lower != 0) {
        square_count -= integer_sqrt(lower - UINT64_C(1));
    }

    return count - square_count;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

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
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    const char *cursor;
    uint64_t lower;
    uint64_t upper;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length == 0 || line[length - 1] != '\n') {
        free(line);
        return EXIT_FAILURE;
    }

    cursor = line;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        free(line);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(&cursor, &lower)) {
        free(line);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        free(line);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(&cursor, &upper)) {
        free(line);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || lower > upper) {
        free(line);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_odd_factors_in_range(lower, upper));

    free(line);
    return EXIT_SUCCESS;
}