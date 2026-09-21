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

static int scanner_get(InputScanner *scanner)
{
    int c;

    if (scanner == NULL || scanner->stream == NULL || scanner->failed) {
        return EOF;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = fgetc(scanner->stream);

    if (c == EOF && ferror(scanner->stream)) {
        scanner->failed = true;
    }

    return c;
}

static bool read_decimal(InputScanner *scanner,
                         uintmax_t positive_limit,
                         uintmax_t negative_limit,
                         bool *negative,
                         uintmax_t *magnitude)
{
    int c;
    bool is_negative = false;
    bool valid = true;
    bool have_digit = false;
    uintmax_t value = 0;
    uintmax_t limit;

    if (scanner == NULL || negative == NULL || magnitude == NULL) {
        return false;
    }

    do {
        c = scanner_get(scanner);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    if (c == '+' || c == '-') {
        is_negative = c == '-';
        c = scanner_get(scanner);
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (c != EOF && !isspace((unsigned char)c)) {
        if (c >= '0' && c <= '9') {
            uintmax_t digit = (uintmax_t)(c - '0');

            have_digit = true;

            if (value > limit / 10 ||
                (value == limit / 10 && digit > limit % 10)) {
                valid = false;
            } else if (valid) {
                value = value * 10 + digit;
            }
        } else {
            valid = false;
        }

        c = scanner_get(scanner);
    }

    if (scanner->failed || !valid || !have_digit) {
        return false;
    }

    *negative = is_negative;
    *magnitude = value;
    return true;
}

static bool read_count(InputScanner *scanner, size_t *count)
{
    bool negative;
    uintmax_t magnitude;

    if (count == NULL ||
        !read_decimal(scanner,
                      (uintmax_t)SIZE_MAX,
                      (uintmax_t)SIZE_MAX,
                      &negative,
                      &magnitude) ||
        negative ||
        magnitude == 0) {
        return false;
    }

    *count = (size_t)magnitude;
    return true;
}

static bool read_int32(InputScanner *scanner, int32_t *value)
{
    bool negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit = (uintmax_t)INT32_MAX + UINTMAX_C(1);

    if (value == NULL ||
        !read_decimal(scanner,
                      (uintmax_t)INT32_MAX,
                      negative_limit,
                      &negative,
                      &magnitude)) {
        return false;
    }

    if (negative) {
        if (magnitude == negative_limit) {
            *value = INT32_MIN;
        } else {
            *value = -(int32_t)magnitude;
        }
    } else {
        *value = (int32_t)magnitude;
    }

    return true;
}

static bool find_maximum_product(const Tuple *tuples,
                                 size_t count,
                                 int64_t *maximum)
{
    int64_t current_maximum;

    if (tuples == NULL || maximum == NULL || count == 0) {
        return false;
    }

    current_maximum =
        (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > current_maximum) {
            current_maximum = product;
        }
    }

    *maximum = current_maximum;
    return true;
}

int main(void)
{
    InputScanner scanner = {
        .stream = stdin,
        .failed = false
    };
    size_t count;
    Tuple *tuples;
    int64_t maximum;

    if (!read_count(&scanner, &count) ||
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
        if (!read_int32(&scanner, &tuples[i].first) ||
            !read_int32(&scanner, &tuples[i].second)) {
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