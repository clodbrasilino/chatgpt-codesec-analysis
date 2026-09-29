#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **line)
{
    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    size_t length = 0;
    size_t capacity = 64;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2;

            if (new_capacity < required) {
                free(buffer);
                return -1;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *buffer = NULL;

    if (read_line(&buffer) != 0) {
        return -1;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end) != 0) {
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

static int read_size(size_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *buffer = NULL;

    if (read_line(&buffer) != 0) {
        return -1;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int triangle_count(size_t rows, size_t *count)
{
    if (count == NULL || rows == 0 || rows == SIZE_MAX) {
        return -1;
    }

    size_t left = rows;
    size_t right = rows + 1;

    if ((left & (size_t)1) == 0) {
        left /= 2;
    } else {
        right /= 2;
    }

    if (left != 0 && right > SIZE_MAX / left) {
        return -1;
    }

    *count = left * right;
    return 0;
}

static int row_start(size_t row, size_t *start)
{
    if (start == NULL) {
        return -1;
    }

    size_t left = row;
    size_t right = row - (row != 0 ? 1 : 0);

    if ((left & (size_t)1) == 0) {
        left /= 2;
    } else {
        right /= 2;
    }

    if (left != 0 && right > SIZE_MAX / left) {
        return -1;
    }

    *start = left * right;
    return 0;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows,
                         int64_t *result)
{
    if (triangle == NULL || result == NULL ||
        rows == 0 || rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    size_t count;

    if (triangle_count(rows, &count) != 0) {
        return -1;
    }

    int64_t *dp = malloc(rows * sizeof(*dp));

    if (dp == NULL) {
        return -1;
    }

    size_t last_start = count - rows;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_start + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t start;

        if (row_start(row, &start) != 0) {
            free(dp);
            return -1;
        }

        for (size_t column = 0; column < row; ++column) {
            int64_t child = dp[column] < dp[column + 1]
                                ? dp[column]
                                : dp[column + 1];

            if (checked_add_int64(triangle[start + column],
                                  child, &dp[column]) != 0) {
                free(dp);
                return -1;
            }
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    size_t rows;
    size_t count;

    if (read_size(&rows) != 0 || triangle_count(rows, &count) != 0) {
        fprintf(stderr, "Invalid row count\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int64_t)) {
        fprintf(stderr, "Triangle is too large\n");
        return EXIT_FAILURE;
    }

    int64_t *triangle = malloc(count * sizeof(*triangle));

    if (triangle == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (read_int64(&triangle[index]) != 0) {
            fprintf(stderr, "Invalid triangle data\n");
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    int64_t result;

    if (minimum_total(triangle, rows, &result) != 0) {
        fprintf(stderr, "Unable to calculate minimum path sum\n");
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}