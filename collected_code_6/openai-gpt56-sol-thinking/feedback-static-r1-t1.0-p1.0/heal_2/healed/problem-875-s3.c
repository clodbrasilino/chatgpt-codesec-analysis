#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_decimal_magnitude(uintmax_t positive_limit,
                                  uintmax_t negative_limit,
                                  int allow_negative,
                                  int *is_negative,
                                  uintmax_t *magnitude)
{
    int ch;
    int negative = 0;
    int has_digit = 0;
    int invalid = 0;
    int overflow = 0;
    uintmax_t value = 0;
    uintmax_t limit;

    if (is_negative == NULL || magnitude == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        if (negative && !allow_negative) {
            invalid = 1;
        }
        ch = fgetc(stdin);
    }

    limit = negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            has_digit = 1;

            if (!overflow) {
                if (value > (limit - digit) / 10) {
                    overflow = 1;
                } else {
                    value = value * 10 + digit;
                }
            }
        } else {
            invalid = 1;
        }

        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        return 0;
    }

    if (!has_digit || invalid || overflow) {
        return 0;
    }

    *is_negative = negative;
    *magnitude = value;
    return 1;
}

static int read_size_value(size_t *value)
{
    int negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_decimal_magnitude((uintmax_t)SIZE_MAX,
                                (uintmax_t)SIZE_MAX,
                                0,
                                &negative,
                                &magnitude) ||
        negative ||
        magnitude == 0) {
        return 0;
    }

    *value = (size_t)magnitude;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    int negative;
    uintmax_t magnitude;
    uintmax_t negative_limit = (uintmax_t)INT64_MAX + 1;

    if (value == NULL ||
        !read_decimal_magnitude((uintmax_t)INT64_MAX,
                                negative_limit,
                                1,
                                &negative,
                                &magnitude)) {
        return 0;
    }

    if (negative) {
        if (magnitude == negative_limit) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return 1;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int find_minimum_pair_difference(const Tuple *tuples,
                                        size_t count,
                                        uint64_t *minimum)
{
    size_t i;

    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    *minimum = absolute_difference(tuples[0].first, tuples[0].second);

    for (i = 1; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < *minimum) {
            *minimum = difference;
        }
    }

    return 1;
}

int main(void)
{
    size_t count;
    size_t i;
    Tuple *tuples;
    uint64_t minimum;

    if (!read_size_value(&count)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (!read_int64_value(&tuples[i].first) ||
            !read_int64_value(&tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_minimum_pair_difference(tuples, count, &minimum)) {
        fputs("Unable to calculate minimum difference\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", minimum);

    free(tuples);
    return EXIT_SUCCESS;
}