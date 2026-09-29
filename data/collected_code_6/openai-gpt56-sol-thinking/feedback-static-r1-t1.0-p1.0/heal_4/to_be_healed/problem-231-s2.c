#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

typedef struct {
    FILE *stream;
    bool end_of_file;
    bool error;
} InputReader;

static bool input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->end_of_file = false;
    reader->error = false;
    return true;
}

static int input_reader_get(InputReader *reader)
{
    int character;

    if (reader == NULL || reader->stream == NULL ||
        reader->error || reader->end_of_file) {
        return EOF;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = fgetc(reader->stream);
    if (character != EOF) {
        return character;
    }

    if (ferror(reader->stream) != 0) {
        reader->error = true;
    } else if (feof(reader->stream) != 0) {
        reader->end_of_file = true;
    } else {
        reader->error = true;
    }

    return EOF;
}

static bool calculate_triangular_number(size_t value, size_t *result)
{
    size_t first;
    size_t second;

    if (result == NULL || value == SIZE_MAX) {
        return false;
    }

    first = value;
    second = value + 1U;

    if ((first & (size_t)1U) == 0U) {
        first /= 2U;
    } else {
        second /= 2U;
    }

    if (second != 0U && first > SIZE_MAX / second) {
        return false;
    }

    *result = first * second;
    return true;
}

static bool calculate_element_count(size_t rows, size_t *count)
{
    if (rows == 0U || count == NULL) {
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

static bool token_ended_validly(const InputReader *reader, int character)
{
    if (reader == NULL || reader->error) {
        return false;
    }

    if (character == EOF) {
        return reader->end_of_file;
    }

    return isspace((unsigned char)character) != 0;
}

static bool read_size_value(InputReader *reader, size_t *result)
{
    size_t value = 0U;
    int character;

    if (reader == NULL || result == NULL) {
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

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        size_t digit = (size_t)(character - '0');

        if (value > (SIZE_MAX - digit) / 10U) {
            return false;
        }

        value = value * 10U + digit;
        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (!token_ended_validly(reader, character)) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *result)
{
    uint64_t magnitude = UINT64_C(0);
    uint64_t limit;
    bool negative = false;
    int character;

    if (reader == NULL || result == NULL) {
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

    if (character < '0' || character > '9') {
        return false;
    }

    limit = negative
                ? (uint64_t)INT64_MAX + UINT64_C(1)
                : (uint64_t)INT64_MAX;

    do {
        uint64_t digit = (uint64_t)(character - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (!token_ended_validly(reader, character)) {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)magnitude;
        }
    } else {
        *result = (int64_t)magnitude;
    }

    return true;
}

static bool input_has_only_trailing_whitespace(InputReader *reader)
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

    return reader->end_of_file && !reader->error;
}

static bool find_max_sum(const int64_t *triangle,
                         size_t rows,
                         int64_t *result)
{
    int64_t *sums;
    size_t element_count;
    size_t allocation_size;
    size_t last_row_offset;

    if (triangle == NULL || result == NULL ||
        !calculate_element_count(rows, &element_count) ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return false;
    }

    allocation_size = rows * sizeof(*sums);
    sums = malloc(allocation_size);
    if (sums == NULL) {
        return false;
    }

    last_row_offset = element_count - rows;

    for (size_t column = 0U; column < rows; ++column) {
        sums[column] = triangle[last_row_offset + column];
    }

    for (size_t next_row = rows - 1U; next_row > 0U; --next_row) {
        size_t row = next_row - 1U;
        size_t row_offset;

        if (!calculate_triangular_number(row, &row_offset)) {
            free(sums);
            return false;
        }

        for (size_t column = 0U; column <= row; ++column) {
            int64_t child = sums[column] > sums[column + 1U]
                                ? sums[column]
                                : sums[column + 1U];

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
    InputReader reader;
    size_t rows;
    size_t element_count;
    size_t allocation_size;
    int64_t *triangle;
    int64_t maximum_sum;

    if (!input_reader_init(&reader, stdin)) {
        fputs("Unable to initialize input reader\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_size_value(&reader, &rows) ||
        !calculate_element_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    allocation_size = element_count * sizeof(*triangle);
    triangle = malloc(allocation_size);
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < element_count; ++index) {
        if (!read_int64_value(&reader, &triangle[index])) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!input_has_only_trailing_whitespace(&reader)) {
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