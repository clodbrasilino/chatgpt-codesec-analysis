#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    size_t capacity;
    size_t length;
    int ch;
    intmax_t parsed;

    if (value == NULL) {
        return -1;
    }

    capacity = 64;
    length = 0;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        discard_line();
        return -1;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                discard_line();
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                discard_line();
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int checked_triangle_size(size_t rows, size_t *element_count)
{
    size_t a;
    size_t b;

    if (element_count == NULL || rows == 0 || rows == SIZE_MAX) {
        return -1;
    }

    a = rows;
    b = rows + 1;

    if ((a & 1U) == 0U) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > SIZE_MAX / a) {
        return -1;
    }

    *element_count = a * b;

    if (*element_count > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows,
                         int64_t *result)
{
    int64_t *dp;
    size_t element_count;
    size_t last_offset;

    if (triangle == NULL || result == NULL ||
        checked_triangle_size(rows, &element_count) != 0 ||
        rows > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    (void)element_count;

    dp = malloc(rows * sizeof(*dp));

    if (dp == NULL) {
        return -1;
    }

    last_offset = rows * (rows - 1) / 2;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t offset = (row - 1) * row / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t minimum;
            int64_t current;

            minimum = dp[column] < dp[column + 1]
                          ? dp[column]
                          : dp[column + 1];
            current = triangle[offset + column];

            if ((minimum > 0 && current > INT64_MAX - minimum) ||
                (minimum < 0 && current < INT64_MIN - minimum)) {
                free(dp);
                return -1;
            }

            dp[column] = current + minimum;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    int64_t input_rows;
    size_t rows;
    size_t element_count;
    int64_t *triangle;
    int64_t result;

    if (read_int64(&input_rows) != 0 || input_rows <= 0 ||
        (uintmax_t)input_rows > (uintmax_t)SIZE_MAX) {
        fputs("Invalid number of rows\n", stderr);
        return EXIT_FAILURE;
    }

    rows = (size_t)input_rows;

    if (checked_triangle_size(rows, &element_count) != 0) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));

    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (read_int64(&triangle[index]) != 0) {
            fputs("Invalid triangle value\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (minimum_total(triangle, rows, &result) != 0) {
        fputs("Unable to calculate minimum path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}