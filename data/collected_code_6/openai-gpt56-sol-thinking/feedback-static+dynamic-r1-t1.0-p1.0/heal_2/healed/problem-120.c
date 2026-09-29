#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

static bool read_count(size_t *count)
{
    int ch;
    size_t parsed = 0;
    bool valid = true;
    bool has_digit = false;
    bool overflow = false;

    if (count == NULL) {
        return false;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    if (ch == '+') {
        ch = fgetc(stdin);
    } else if (ch == '-') {
        valid = false;
        ch = fgetc(stdin);
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            size_t digit = (size_t)(ch - '0');

            has_digit = true;

            if (!overflow) {
                if (parsed > (SIZE_MAX - digit) / 10) {
                    overflow = true;
                } else {
                    parsed = parsed * 10 + digit;
                }
            }
        } else {
            valid = false;
        }

        ch = fgetc(stdin);
    }

    if (ferror(stdin) || !valid || !has_digit || overflow || parsed == 0) {
        return false;
    }

    *count = parsed;
    return true;
}

static bool read_int32(int32_t *value)
{
    int ch;
    uintmax_t magnitude = 0;
    uintmax_t limit;
    bool negative = false;
    bool valid = true;
    bool has_digit = false;
    bool overflow = false;

    if (value == NULL) {
        return false;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        ch = fgetc(stdin);
    }

    limit = negative
        ? (uintmax_t)(-(INT32_MIN + 1)) + UINTMAX_C(1)
        : (uintmax_t)INT32_MAX;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            has_digit = true;

            if (!overflow) {
                if (magnitude > (limit - digit) / UINTMAX_C(10)) {
                    overflow = true;
                } else {
                    magnitude = magnitude * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        ch = fgetc(stdin);
    }

    if (ferror(stdin) || !valid || !has_digit || overflow) {
        return false;
    }

    if (negative) {
        if (magnitude == limit) {
            *value = INT32_MIN;
        } else {
            *value = -(int32_t)magnitude;
        }
    } else {
        *value = (int32_t)magnitude;
    }

    return true;
}

static bool find_maximum_product(const Tuple *tuples, size_t count,
                                 int64_t *maximum)
{
    if (tuples == NULL || maximum == NULL || count == 0) {
        return false;
    }

    *maximum = (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > *maximum) {
            *maximum = product;
        }
    }

    return true;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t maximum;

    if (!read_count(&count) || count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32(&tuples[i].first) ||
            !read_int32(&tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_product(tuples, count, &maximum)) {
        fputs("Unable to find maximum product\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}