#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    FILE *stream;
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool io_error;
} TokenReader;

static void token_reader_init(TokenReader *reader, FILE *stream)
{
    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    reader->io_error = false;
}

static int token_reader_next_char(TokenReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->io_error) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1,
                               sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                reader->io_error = true;
            }
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool read_decimal_token(TokenReader *reader,
                               bool allow_negative,
                               uintmax_t positive_limit,
                               uintmax_t negative_limit,
                               bool *negative,
                               uintmax_t *magnitude)
{
    int ch;
    bool is_negative = false;
    bool have_digit = false;
    bool valid = true;
    uintmax_t value = 0;
    uintmax_t limit;

    if (reader == NULL || negative == NULL || magnitude == NULL) {
        return false;
    }

    do {
        ch = token_reader_next_char(reader);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    if (ch == '+' || ch == '-') {
        is_negative = ch == '-';
        ch = token_reader_next_char(reader);
    }

    if (is_negative && !allow_negative) {
        valid = false;
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            have_digit = true;

            if (valid) {
                if (value > limit / UINTMAX_C(10) ||
                    (value == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    valid = false;
                } else {
                    value = value * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        ch = token_reader_next_char(reader);
    }

    if (reader->io_error || !valid || !have_digit) {
        return false;
    }

    *negative = is_negative;
    *magnitude = value;
    return true;
}

static bool read_size(TokenReader *reader, size_t *value)
{
    bool negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_decimal_token(reader, false, (uintmax_t)SIZE_MAX,
                            UINTMAX_C(0), &negative, &magnitude)) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int64(TokenReader *reader, int64_t *value)
{
    bool negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);

    if (value == NULL ||
        !read_decimal_token(reader, true, (uintmax_t)INT64_MAX,
                            negative_limit, &negative, &magnitude)) {
        return false;
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

    return true;
}

static bool multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return false;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && b < INT64_MAX / a)) {
            return false;
        }
    }

    *result = a * b;
    return true;
}

bool find_maximum_tuple_product(const Tuple *tuples,
                                size_t count,
                                int64_t *maximum_product)
{
    int64_t maximum = INT64_MIN;

    if (tuples == NULL || maximum_product == NULL || count == 0) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t product;

        if (!multiply_checked(tuples[i].first,
                              tuples[i].second,
                              &product)) {
            return false;
        }

        if (product > maximum) {
            maximum = product;
        }
    }

    *maximum_product = maximum;
    return true;
}

int main(void)
{
    TokenReader reader;
    size_t count;
    Tuple *tuples;
    int64_t maximum_product;

    token_reader_init(&reader, stdin);

    if (!read_size(&reader, &count) ||
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
        if (!read_int64(&reader, &tuples[i].first) ||
            !read_int64(&reader, &tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_tuple_product(tuples, count, &maximum_product)) {
        fputs("Unable to calculate maximum product\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum_product) < 0) {
        fputs("Output error\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}