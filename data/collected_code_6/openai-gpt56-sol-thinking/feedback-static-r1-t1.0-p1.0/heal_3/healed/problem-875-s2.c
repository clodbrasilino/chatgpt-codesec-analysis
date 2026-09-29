#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool end_of_file;
    bool input_error;
} InputReader;

typedef enum {
    READ_ERROR = -1,
    READ_END = 0,
    READ_SUCCESS = 1
} ReadStatus;

static ReadStatus read_byte(InputReader *reader, unsigned char *byte)
{
    if (reader == NULL || byte == NULL) {
        return READ_ERROR;
    }

    if (reader->position == reader->length) {
        if (reader->input_error) {
            return READ_ERROR;
        }

        if (reader->end_of_file) {
            return READ_END;
        }

        reader->length = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer),
            stdin);
        reader->position = 0;

        if (reader->length < sizeof(reader->buffer)) {
            if (ferror(stdin)) {
                reader->input_error = true;
            } else if (feof(stdin)) {
                reader->end_of_file = true;
            }
        }

        if (reader->length == 0) {
            return reader->input_error ? READ_ERROR : READ_END;
        }
    }

    *byte = reader->buffer[reader->position++];
    return READ_SUCCESS;
}

static bool read_decimal_token(
    InputReader *reader,
    bool allow_negative,
    uintmax_t positive_limit,
    uintmax_t negative_limit,
    bool *is_negative,
    uintmax_t *magnitude)
{
    if (reader == NULL || is_negative == NULL || magnitude == NULL) {
        return false;
    }

    unsigned char character;
    ReadStatus status;

    do {
        status = read_byte(reader, &character);

        if (status != READ_SUCCESS) {
            return false;
        }
    } while (isspace(character));

    bool negative = false;
    bool valid = true;
    bool has_digit = false;
    uintmax_t value = 0;

    if (character == '+' || character == '-') {
        negative = character == '-';

        if (negative && !allow_negative) {
            valid = false;
        }

        status = read_byte(reader, &character);
    }

    const uintmax_t limit =
        negative && allow_negative ? negative_limit : positive_limit;

    while (status == READ_SUCCESS && !isspace(character)) {
        if (character >= '0' && character <= '9') {
            const uintmax_t digit = (uintmax_t)(character - '0');
            has_digit = true;

            if (value > limit / 10 ||
                (value == limit / 10 && digit > limit % 10)) {
                valid = false;
            } else {
                value = value * 10 + digit;
            }
        } else {
            valid = false;
        }

        status = read_byte(reader, &character);
    }

    if (status == READ_ERROR || reader->input_error) {
        return false;
    }

    if (!valid || !has_digit) {
        return false;
    }

    *is_negative = negative;
    *magnitude = value;
    return true;
}

static bool read_size(InputReader *reader, size_t *value)
{
    if (reader == NULL || value == NULL) {
        return false;
    }

    bool negative;
    uintmax_t magnitude;

    if (!read_decimal_token(
            reader,
            false,
            (uintmax_t)SIZE_MAX,
            (uintmax_t)SIZE_MAX,
            &negative,
            &magnitude)) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int64(InputReader *reader, int64_t *value)
{
    if (reader == NULL || value == NULL) {
        return false;
    }

    bool negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit = (uintmax_t)INT64_MAX + UINTMAX_C(1);

    if (!read_decimal_token(
            reader,
            true,
            (uintmax_t)INT64_MAX,
            negative_limit,
            &negative,
            &magnitude)) {
        return false;
    }

    if (!negative) {
        *value = (int64_t)magnitude;
    } else if (magnitude == negative_limit) {
        *value = INT64_MIN;
    } else {
        *value = -(int64_t)magnitude;
    }

    return true;
}

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}

static bool find_minimum_tuple_difference(
    const Tuple *tuples,
    size_t count,
    uint64_t *minimum_difference)
{
    if (tuples == NULL || count == 0 || minimum_difference == NULL) {
        return false;
    }

    uint64_t minimum = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        const uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < minimum) {
            minimum = difference;
        }
    }

    *minimum_difference = minimum;
    return true;
}

int main(void)
{
    InputReader reader = {0};
    size_t count;

    if (!read_size(&reader, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));

    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&reader, &tuples[i].first) ||
            !read_int64(&reader, &tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    uint64_t minimum_difference;

    if (!find_minimum_tuple_difference(
            tuples,
            count,
            &minimum_difference)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum_difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}