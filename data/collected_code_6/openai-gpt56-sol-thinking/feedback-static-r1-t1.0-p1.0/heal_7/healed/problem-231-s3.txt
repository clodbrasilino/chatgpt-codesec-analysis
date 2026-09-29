#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    bool end_reached;
    bool error;
} InputReader;

static bool input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->end_reached = false;
    reader->error = false;

    return true;
}

static int input_reader_get(InputReader *reader)
{
    int ch;

    if (reader == NULL || reader->stream == NULL || reader->end_reached) {
        return EOF;
    }

    ch = fgetc(reader->stream);

    if (ch == EOF) {
        if (ferror(reader->stream) != 0 || feof(reader->stream) == 0) {
            reader->error = true;
        }

        reader->end_reached = true;
    }

    return ch;
}

static bool input_reader_has_only_whitespace(InputReader *reader)
{
    int ch;

    if (reader == NULL || reader->stream == NULL) {
        return false;
    }

    while ((ch = input_reader_get(reader)) != EOF) {
        if (isspace((unsigned char)ch) == 0) {
            return false;
        }
    }

    return !reader->error;
}

static bool read_uintmax_decimal(InputReader *reader, uintmax_t *result)
{
    uintmax_t value = UINTMAX_C(0);
    bool have_digit = false;
    int ch;

    if (reader == NULL || reader->stream == NULL || result == NULL) {
        return false;
    }

    do {
        ch = input_reader_get(reader);
    } while (ch != EOF && isspace((unsigned char)ch) != 0);

    if (ch == EOF) {
        return false;
    }

    if (ch == '+') {
        ch = input_reader_get(reader);
    } else if (ch == '-') {
        return false;
    }

    while (ch != EOF && isspace((unsigned char)ch) == 0) {
        uintmax_t digit;

        if (ch < '0' || ch > '9') {
            return false;
        }

        digit = (uintmax_t)(ch - '0');

        if (value > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
            return false;
        }

        value = value * UINTMAX_C(10) + digit;
        have_digit = true;
        ch = input_reader_get(reader);
    }

    if (!have_digit || reader->error) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_decimal(InputReader *reader, int64_t *result)
{
    uintmax_t magnitude = UINTMAX_C(0);
    uintmax_t limit;
    bool negative = false;
    bool have_digit = false;
    int ch;

    if (reader == NULL || reader->stream == NULL || result == NULL) {
        return false;
    }

    do {
        ch = input_reader_get(reader);
    } while (ch != EOF && isspace((unsigned char)ch) != 0);

    if (ch == EOF) {
        return false;
    }

    if (ch == '-' || ch == '+') {
        negative = ch == '-';
        ch = input_reader_get(reader);
    }

    limit = negative
        ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
        : (uintmax_t)INT64_MAX;

    while (ch != EOF && isspace((unsigned char)ch) == 0) {
        uintmax_t digit;

        if (ch < '0' || ch > '9') {
            return false;
        }

        digit = (uintmax_t)(ch - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;
        have_digit = true;
        ch = input_reader_get(reader);
    }

    if (!have_digit || reader->error) {
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

static bool triangle_element_count(size_t rows, size_t *count)
{
    size_t factor_a;
    size_t factor_b;

    if (count == NULL || rows == SIZE_MAX) {
        return false;
    }

    if (rows % 2U == 0U) {
        factor_a = rows / 2U;
        factor_b = rows + 1U;
    } else {
        factor_a = rows;
        factor_b = (rows + 1U) / 2U;
    }

    if (factor_a != 0U && factor_b > SIZE_MAX / factor_a) {
        return false;
    }

    *count = factor_a * factor_b;
    return true;
}

static bool checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > INT64_C(0) && a > INT64_MAX - b) ||
        (b < INT64_C(0) && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
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

    if (!read_uintmax_decimal(&reader, &input_rows)) {
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

    for (size_t i = 0U; i < element_count; ++i) {
        if (!read_int64_decimal(&reader, &triangle[i])) {
            fputs("Invalid triangle data\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!input_reader_has_only_whitespace(&reader)) {
        fputs("Unexpected input data\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    if (!maximum_triangle_sum(triangle, rows, element_count, &maximum)) {
        fputs("Unable to calculate maximum sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (fprintf(stdout, "%" PRId64 "\n", maximum) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}