#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool exhausted;
    bool failed;
} InputReader;

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL ||
        reader->stream == NULL ||
        reader->exhausted) {
        return EOF;
    }

    if (reader->position >= reader->length) {
        if (reader->failed) {
            reader->exhausted = true;
            return EOF;
        }

        reader->position = 0;
        reader->length = fread(reader->buffer,
                               sizeof(reader->buffer[0]),
                               sizeof(reader->buffer),
                               reader->stream);

        if (ferror(reader->stream) != 0) {
            reader->failed = true;
        }

        if (reader->length == 0) {
            reader->exhausted = true;
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool calculate_triangular_number(size_t value, size_t *result)
{
    size_t first;
    size_t second;

    if (result == NULL || value == SIZE_MAX) {
        return false;
    }

    first = value;
    second = value + 1;

    if ((first & (size_t)1) == 0) {
        first /= 2;
    } else {
        second /= 2;
    }

    if (second != 0 && first > SIZE_MAX / second) {
        return false;
    }

    *result = first * second;
    return true;
}

static bool calculate_element_count(size_t rows, size_t *count)
{
    if (count == NULL || rows == 0) {
        return false;
    }

    return calculate_triangular_number(rows, count);
}

static bool checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return false;
    }

    *result = left + right;
    return true;
}

static bool finish_numeric_input(const InputReader *reader, int character)
{
    if (reader == NULL) {
        return false;
    }

    if (character == EOF) {
        return !reader->failed;
    }

    return isspace((unsigned char)character) != 0;
}

static bool read_size_value(InputReader *reader, size_t *value)
{
    size_t parsed = 0;
    int character;

    if (reader == NULL || value == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    if (character == EOF) {
        return false;
    }

    if (character == '+') {
        character = input_reader_get(reader);
    } else if (character == '-') {
        return false;
    }

    if (character == EOF ||
        isdigit((unsigned char)character) == 0) {
        return false;
    }

    while (character != EOF &&
           isdigit((unsigned char)character) != 0) {
        unsigned int digit = (unsigned int)(character - '0');

        if (parsed > (SIZE_MAX - (size_t)digit) / (size_t)10) {
            return false;
        }

        parsed = parsed * (size_t)10 + (size_t)digit;
        character = input_reader_get(reader);
    }

    if (!finish_numeric_input(reader, character)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *value)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    bool negative = false;
    int character;

    if (reader == NULL || value == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    if (character == EOF) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_reader_get(reader);
    }

    if (character == EOF ||
        isdigit((unsigned char)character) == 0) {
        return false;
    }

    limit = negative
                ? (uint64_t)INT64_MAX + UINT64_C(1)
                : (uint64_t)INT64_MAX;

    while (character != EOF &&
           isdigit((unsigned char)character) != 0) {
        unsigned int digit = (unsigned int)(character - '0');

        if (magnitude >
            (limit - (uint64_t)digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + (uint64_t)digit;
        character = input_reader_get(reader);
    }

    if (!finish_numeric_input(reader, character)) {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

static bool input_is_exhausted(InputReader *reader)
{
    int character;

    if (reader == NULL) {
        return false;
    }

    while ((character = input_reader_get(reader)) != EOF) {
        if (isspace((unsigned char)character) == 0) {
            return false;
        }
    }

    return !reader->failed;
}

static bool find_max_sum(const int64_t *triangle,
                         size_t rows,
                         int64_t *result)
{
    int64_t *sums;
    size_t element_count;
    size_t row;
    size_t row_offset;

    if (triangle == NULL ||
        result == NULL ||
        !calculate_element_count(rows, &element_count) ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return false;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return false;
    }

    row_offset = element_count - rows;

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[row_offset + column];
    }

    row = rows - 1;

    while (row > 0) {
        --row;
        row_offset -= row + 1;

        for (size_t column = 0; column <= row; ++column) {
            int64_t child = sums[column] > sums[column + 1]
                                ? sums[column]
                                : sums[column + 1];

            if (!checked_add_int64(triangle[row_offset + column],
                                   child,
                                   &sums[column])) {
                free(sums);
                return false;
            }
        }
    }

    *result = sums[0];
    free(sums);
    return true;
}

int main(void)
{
    InputReader reader = {
        .stream = stdin,
        .buffer = {0},
        .position = 0,
        .length = 0,
        .exhausted = false,
        .failed = false
    };
    size_t rows;
    size_t element_count;
    int64_t *triangle;
    int64_t maximum_sum;

    if (!read_size_value(&reader, &rows) ||
        !calculate_element_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (!read_int64_value(&reader, &triangle[index])) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!input_is_exhausted(&reader)) {
        fputs("Invalid input\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    if (!find_max_sum(triangle, rows, &maximum_sum)) {
        fputs("Unable to calculate maximum sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", maximum_sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}