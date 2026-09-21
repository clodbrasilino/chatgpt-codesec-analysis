#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    int error;
    int end_of_file;
} InputReader;

static int read_input_character(InputReader *reader)
{
    if (reader == NULL || reader->error || reader->end_of_file) {
        return EOF;
    }

    if (reader->position >= reader->length) {
        reader->length = fread(reader->buffer, 1, sizeof(reader->buffer), stdin);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(stdin)) {
                reader->error = 1;
            } else {
                reader->end_of_file = 1;
            }

            return EOF;
        }

        if (reader->length < sizeof(reader->buffer) && ferror(stdin)) {
            reader->error = 1;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int read_decimal_magnitude(InputReader *reader,
                                  uintmax_t positive_limit,
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

    if (reader == NULL || is_negative == NULL || magnitude == NULL) {
        return 0;
    }

    do {
        ch = read_input_character(reader);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';

        if (negative && !allow_negative) {
            invalid = 1;
        }

        ch = read_input_character(reader);
    }

    limit = negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            has_digit = 1;

            if (!overflow) {
                if (digit > limit ||
                    value > (limit - digit) / UINTMAX_C(10)) {
                    overflow = 1;
                } else {
                    value = value * UINTMAX_C(10) + digit;
                }
            }
        } else {
            invalid = 1;
        }

        ch = read_input_character(reader);
    }

    if (reader->error || !has_digit || invalid || overflow) {
        return 0;
    }

    *is_negative = negative;
    *magnitude = value;
    return 1;
}

static int read_size_value(InputReader *reader, size_t *value)
{
    int negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_decimal_magnitude(reader,
                                (uintmax_t)SIZE_MAX,
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

static int read_int64_value(InputReader *reader, int64_t *value)
{
    int negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);

    if (value == NULL ||
        !read_decimal_magnitude(reader,
                                (uintmax_t)INT64_MAX,
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

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}

int main(void)
{
    InputReader reader = {{0}, 0, 0, 0, 0};
    size_t count;
    uint64_t minimum = 0;

    if (!read_size_value(&reader, &count)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t first;
        int64_t second;
        uint64_t difference;

        if (!read_int64_value(&reader, &first) ||
            !read_int64_value(&reader, &second)) {
            fputs("Invalid tuple input\n", stderr);
            return EXIT_FAILURE;
        }

        difference = absolute_difference(first, second);

        if (i == 0 || difference < minimum) {
            minimum = difference;
        }
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}