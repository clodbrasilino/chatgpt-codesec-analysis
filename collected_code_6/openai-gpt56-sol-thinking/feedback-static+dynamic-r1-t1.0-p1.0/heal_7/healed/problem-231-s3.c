#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

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
        reader->end_of_file || reader->error) {
        return EOF;
    }

    character = fgetc(reader->stream);

    if (character == EOF) {
        if (ferror(reader->stream) != 0) {
            reader->error = true;
        } else {
            reader->end_of_file = true;
        }
    }

    return character;
}

static bool input_reader_failed(const InputReader *reader)
{
    return reader == NULL || reader->error;
}

static bool is_input_space(int character)
{
    return character == ' ' ||
           character == '\t' ||
           character == '\n' ||
           character == '\r' ||
           character == '\f' ||
           character == '\v';
}

static bool triangle_element_count(size_t rows, size_t *count)
{
    size_t first_factor;
    size_t second_factor;

    if (count == NULL || rows == SIZE_MAX) {
        return false;
    }

    if (rows % 2U == 0U) {
        first_factor = rows / 2U;
        second_factor = rows + 1U;
    } else {
        first_factor = rows;
        second_factor = (rows + 1U) / 2U;
    }

    if (first_factor != 0U &&
        second_factor > SIZE_MAX / first_factor) {
        return false;
    }

    *count = first_factor * second_factor;
    return true;
}

static bool checked_add_int64(int64_t first, int64_t second,
                              int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((second > 0 && first > INT64_MAX - second) ||
        (second < 0 && first < INT64_MIN - second)) {
        return false;
    }

    *result = first + second;
    return true;
}

static bool read_nonspace(InputReader *reader, int *character)
{
    int current;

    if (reader == NULL || character == NULL) {
        return false;
    }

    do {
        current = input_reader_get(reader);
    } while (current != EOF && is_input_space(current));

    if (current == EOF) {
        return false;
    }

    *character = current;
    return true;
}

static bool read_uintmax_value(InputReader *reader, uintmax_t *result)
{
    uintmax_t value = UINTMAX_C(0);
    int character;

    if (reader == NULL || result == NULL ||
        !read_nonspace(reader, &character)) {
        return false;
    }

    if (character == '+') {
        character = input_reader_get(reader);
    }

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        uintmax_t digit = (uintmax_t)(character - '0');

        if (value > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
            return false;
        }

        value = value * UINTMAX_C(10) + digit;
        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (character != EOF && !is_input_space(character)) {
        return false;
    }

    if (input_reader_failed(reader)) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *result)
{
    uintmax_t magnitude = UINTMAX_C(0);
    uintmax_t limit;
    bool negative = false;
    int character;

    if (reader == NULL || result == NULL ||
        !read_nonspace(reader, &character)) {
        return false;
    }

    if (character == '-' || character == '+') {
        negative = character == '-';
        character = input_reader_get(reader);
    }

    if (character < '0' || character > '9') {
        return false;
    }

    limit = negative
                ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
                : (uintmax_t)INT64_MAX;

    do {
        uintmax_t digit = (uintmax_t)(character - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;
        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (character != EOF && !is_input_space(character)) {
        return false;
    }

    if (input_reader_failed(reader)) {
        return false;
    }

    if (negative) {
        if (magnitude == (uintmax_t)INT64_MAX + UINTMAX_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)magnitude;
        }
    } else {
        *result = (int64_t)magnitude;
    }

    return true;
}

static bool maximum_triangle_sum(const int64_t *triangle,
                                 size_t rows,
                                 size_t element_count,
                                 int64_t *result)
{
    int64_t *sums;
    size_t expected_count;
    size_t last_row_start;
    size_t row;

    if (result == NULL ||
        !triangle_element_count(rows, &expected_count) ||
        expected_count != element_count) {
        return false;
    }

    if (rows == 0U) {
        *result = INT64_C(0);
        return true;
    }

    if (triangle == NULL || rows > SIZE_MAX / sizeof(*sums)) {
        return false;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return false;
    }

    last_row_start = element_count - rows;

    for (size_t column = 0U; column < rows; ++column) {
        sums[column] = triangle[last_row_start + column];
    }

    row = rows - 1U;

    while (row > 0U) {
        size_t row_start;

        --row;

        if (!triangle_element_count(row, &row_start)) {
            free(sums);
            return false;
        }

        for (size_t column = 0U; column <= row; ++column) {
            int64_t best_child;

            if (sums[column] > sums[column + 1U]) {
                best_child = sums[column];
            } else {
                best_child = sums[column + 1U];
            }

            if (!checked_add_int64(triangle[row_start + column],
                                   best_child,
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
    uintmax_t input_rows;
    size_t rows;
    size_t element_count;
    int64_t *triangle = NULL;
    int64_t maximum;

    if (!input_reader_init(&reader, stdin)) {
        fputs("Input initialization failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_uintmax_value(&reader, &input_rows)) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    if (input_rows > (uintmax_t)SIZE_MAX) {
        fputs("Row count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    rows = (size_t)input_rows;

    if (!triangle_element_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (element_count != 0U) {
        triangle = malloc(element_count * sizeof(*triangle));
        if (triangle == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0U; index < element_count; ++index) {
        if (!read_int64_value(&reader, &triangle[index])) {
            fputs("Invalid triangle data\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_triangle_sum(triangle,
                              rows,
                              element_count,
                              &maximum)) {
        fputs("Unable to calculate maximum sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (fprintf(stdout, "%" PRId64 "\n", maximum) < 0 ||
        fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}