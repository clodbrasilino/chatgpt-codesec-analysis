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

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (value == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            discard_line();
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    discard_line();
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);

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

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return -1;
        }

        buffer = new_buffer;
        capacity = length + 1;
    }

    buffer[length] = '\0';

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(buffer, &end, 10);

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

static int minimum_total(const int64_t *triangle, size_t rows,
                         int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1) ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    size_t element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(*triangle)) {
        return -1;
    }

    int64_t *dp = malloc(rows * sizeof(*dp));

    if (dp == NULL) {
        return -1;
    }

    size_t last_offset = rows * (rows - 1) / 2;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t offset = (row - 1) * row / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t minimum =
                dp[column] < dp[column + 1] ? dp[column] : dp[column + 1];
            int64_t current = triangle[offset + column];

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

    if (read_int64(&input_rows) != 0 || input_rows <= 0 ||
        (uintmax_t)input_rows > (uintmax_t)SIZE_MAX) {
        fputs("Invalid number of rows\n", stderr);
        return EXIT_FAILURE;
    }

    size_t rows = (size_t)input_rows;

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    size_t element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *triangle = malloc(element_count * sizeof(*triangle));

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

    int64_t result;

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