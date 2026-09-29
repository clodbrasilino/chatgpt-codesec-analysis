#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
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
    if (reader == NULL || reader->stream == NULL || byte == NULL) {
        return READ_ERROR;
    }

    if (reader->input_error) {
        return READ_ERROR;
    }

    if (reader->position < reader->length) {
        *byte = reader->buffer[reader->position++];
        return READ_SUCCESS;
    }

    if (reader->end_of_file) {
        return READ_END;
    }

    reader->position = 0;
    reader->length = fread(
        reader->buffer,
        sizeof(reader->buffer[0]),
        INPUT_BUFFER_SIZE,
        reader->stream);

    if (ferror(reader->stream)) {
        reader->input_error = true;
        reader->length = 0;
        return READ_ERROR;
    }

    if (reader->length == 0) {
        reader->end_of_file = true;
        return READ_END;
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

    unsigned char character = 0;
    ReadStatus status;

    do {
        status = read_byte(reader, &character);

        if (status != READ_SUCCESS) {
            return false;
        }
    } while (isspace((int)character) != 0);

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

    while (status == READ_SUCCESS && isspace((int)character) == 0) {
        if (character >= '0' && character <= '9') {
            const uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = true;

            if (value > limit / UINTMAX_C(10) ||
                (value == limit / UINTMAX_C(10) &&
                 digit > limit % UINTMAX_C(10))) {
                valid = false;
            } else {
                value = value * UINTMAX_C(10) + digit;
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
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);

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
    InputReader reader = {
        .stream = stdin,
        .buffer = {0},
        .position = 0,
        .length = 0,
        .end_of_file = false,
        .input_error = false
    };

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