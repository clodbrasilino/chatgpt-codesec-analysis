#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool ended;
    bool error;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    reader->stream = stream;
    reader->position = 0U;
    reader->length = 0U;
    reader->ended = false;
    reader->error = false;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->ended) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1U,
                               sizeof(reader->buffer), reader->stream);
        reader->position = 0U;

        if (reader->length == 0U) {
            reader->error = ferror(reader->stream) != 0;
            reader->ended = true;
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool input_reader_failed(const InputReader *reader)
{
    return reader == NULL || reader->error;
}

static bool triangle_element_count(size_t rows, size_t *count)
{
    size_t a;
    size_t b;

    if (count == NULL || rows == SIZE_MAX) {
        return false;
    }

    if (rows % 2U == 0U) {
        a = rows / 2U;
        b = rows + 1U;
    } else {
        a = rows;
        b = (rows + 1U) / 2U;
    }

    if (a != 0U && b > SIZE_MAX / a) {
        return false;
    }

    *count = a * b;
    return true;
}

static bool checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool read_nonspace(InputReader *reader, int *character)
{
    int c;

    if (reader == NULL || character == NULL) {
        return false;
    }

    do {
        c = input_reader_get(reader);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    *character = c;
    return true;
}

static bool read_uintmax_value(InputReader *reader, uintmax_t *result)
{
    uintmax_t value = 0U;
    int c;

    if (result == NULL || !read_nonspace(reader, &c)) {
        return false;
    }

    if (c == '+') {
        c = input_reader_get(reader);
    }

    if (c < '0' || c > '9') {
        return false;
    }

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (value > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
            return false;
        }

        value = value * UINTMAX_C(10) + digit;
        c = input_reader_get(reader);
    } while (c >= '0' && c <= '9');

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (c == EOF && input_reader_failed(reader)) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *result)
{
    uintmax_t magnitude = 0U;
    uintmax_t limit;
    bool negative = false;
    int c;

    if (result == NULL || !read_nonspace(reader, &c)) {
        return false;
    }

    if (c == '-' || c == '+') {
        negative = c == '-';
        c = input_reader_get(reader);
    }

    if (c < '0' || c > '9') {
        return false;
    }

    limit = negative
                ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
                : (uintmax_t)INT64_MAX;

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;
        c = input_reader_get(reader);
    } while (c >= '0' && c <= '9');

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (c == EOF && input_reader_failed(reader)) {
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

static bool maximum_triangle_sum(const int64_t *triangle, size_t rows,
                                 size_t element_count, int64_t *result)
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
        *result = 0;
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
            int64_t best_child = sums[column] > sums[column + 1U]
                                     ? sums[column]
                                     : sums[column + 1U];

            if (!checked_add_int64(triangle[row_start + column],
                                   best_child, &sums[column])) {
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

    input_reader_init(&reader, stdin);

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

    if (element_count > 0U) {
        triangle = malloc(element_count * sizeof(*triangle));
        if (triangle == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < element_count; ++i) {
        if (!read_int64_value(&reader, &triangle[i])) {
            fputs("Invalid triangle data\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_triangle_sum(triangle, rows, element_count, &maximum)) {
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