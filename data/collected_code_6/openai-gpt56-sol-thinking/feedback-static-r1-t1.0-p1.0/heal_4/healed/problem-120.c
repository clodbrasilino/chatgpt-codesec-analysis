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

typedef struct {
    FILE *stream;
    bool failed;
} InputScanner;

static int scanner_get_byte(InputScanner *scanner)
{
    int byte;

    if (scanner == NULL || scanner->stream == NULL || scanner->failed) {
        return EOF;
    }

    byte = fgetc(scanner->stream);
    if (byte == EOF && ferror(scanner->stream)) {
        scanner->failed = true;
    }

    return byte;
}

static bool read_decimal_value(InputScanner *scanner,
                               bool allow_negative,
                               uintmax_t positive_limit,
                               uintmax_t negative_limit,
                               uintmax_t *magnitude,
                               bool *negative)
{
    int byte;
    uintmax_t result = 0;
    uintmax_t limit;
    bool is_negative = false;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;

    if (scanner == NULL || magnitude == NULL || negative == NULL) {
        return false;
    }

    do {
        byte = scanner_get_byte(scanner);
        if (byte == EOF) {
            return false;
        }
    } while (isspace((unsigned char)byte));

    if (byte == '+' || byte == '-') {
        is_negative = byte == '-';

        if (is_negative && !allow_negative) {
            valid = false;
        }

        byte = scanner_get_byte(scanner);
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (byte != EOF && !isspace((unsigned char)byte)) {
        if (byte >= '0' && byte <= '9') {
            uintmax_t digit = (uintmax_t)(byte - '0');

            has_digit = true;

            if (!overflow) {
                if (result > (limit - digit) / UINTMAX_C(10)) {
                    overflow = true;
                } else {
                    result = result * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        byte = scanner_get_byte(scanner);
    }

    if (scanner->failed || !has_digit || !valid || overflow) {
        return false;
    }

    *magnitude = result;
    *negative = is_negative;
    return true;
}

static bool read_size_value(InputScanner *scanner, size_t *value)
{
    uintmax_t magnitude;
    bool negative;

    if (value == NULL ||
        !read_decimal_value(scanner, false, SIZE_MAX, SIZE_MAX,
                            &magnitude, &negative)) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int32_value(InputScanner *scanner, int32_t *value)
{
    const uintmax_t positive_limit = (uintmax_t)INT32_MAX;
    const uintmax_t negative_limit =
        (uintmax_t)INT32_MAX + UINTMAX_C(1);
    uintmax_t magnitude;
    bool negative;

    if (value == NULL ||
        !read_decimal_value(scanner, true,
                            positive_limit, negative_limit,
                            &magnitude, &negative)) {
        return false;
    }

    if (!negative) {
        *value = (int32_t)magnitude;
    } else if (magnitude == negative_limit) {
        *value = INT32_MIN;
    } else {
        *value = -(int32_t)magnitude;
    }

    return true;
}

static bool find_maximum_product(const Tuple *tuples,
                                 size_t count,
                                 int64_t *maximum)
{
    int64_t result;

    if (tuples == NULL || maximum == NULL || count == 0) {
        return false;
    }

    result = (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > result) {
            result = product;
        }
    }

    *maximum = result;
    return true;
}

int main(void)
{
    InputScanner scanner = { stdin, false };
    size_t count;
    Tuple *tuples;
    int64_t maximum;

    if (!read_size_value(&scanner, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32_value(&scanner, &tuples[i].first) ||
            !read_int32_value(&scanner, &tuples[i].second)) {
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

    free(tuples);

    if (printf("%" PRId64 "\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}