#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_uintmax_decimal(FILE *stream, uintmax_t *result)
{
    uintmax_t value = 0;
    bool have_digit = false;
    int ch;

    if (stream == NULL || result == NULL) {
        return false;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    if (ch == '+') {
        ch = fgetc(stream);
    } else if (ch == '-') {
        return false;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        uintmax_t digit;

        if (ch < '0' || ch > '9') {
            return false;
        }

        digit = (uintmax_t)(ch - '0');
        if (value > (UINTMAX_MAX - digit) / 10U) {
            return false;
        }

        value = value * 10U + digit;
        have_digit = true;
        ch = fgetc(stream);
    }

    if (!have_digit || (ch == EOF && ferror(stream))) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_decimal(FILE *stream, int64_t *result)
{
    uintmax_t magnitude = 0;
    uintmax_t limit;
    bool negative = false;
    bool have_digit = false;
    int ch;

    if (stream == NULL || result == NULL) {
        return false;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    if (ch == '-' || ch == '+') {
        negative = ch == '-';
        ch = fgetc(stream);
    }

    limit = negative
                ? (uintmax_t)INT64_MAX + 1U
                : (uintmax_t)INT64_MAX;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        uintmax_t digit;

        if (ch < '0' || ch > '9') {
            return false;
        }

        digit = (uintmax_t)(ch - '0');
        if (magnitude > (limit - digit) / 10U) {
            return false;
        }

        magnitude = magnitude * 10U + digit;
        have_digit = true;
        ch = fgetc(stream);
    }

    if (!have_digit || (ch == EOF && ferror(stream))) {
        return false;
    }

    if (negative) {
        if (magnitude == (uintmax_t)INT64_MAX + 1U) {
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
    uintmax_t input_rows;
    size_t rows;
    size_t element_count;
    int64_t *triangle = NULL;
    int64_t maximum;

    if (!read_uintmax_decimal(stdin, &input_rows)) {
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
        if (!read_int64_decimal(stdin, &triangle[i])) {
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