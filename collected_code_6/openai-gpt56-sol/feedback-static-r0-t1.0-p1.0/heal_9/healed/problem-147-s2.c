#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int read_line(char **buffer)
{
    char *line;
    size_t length = 0;
    size_t capacity = 128;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            if (length > 0 && line[length - 1] == '\r') {
                --length;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int triangle_element_count(size_t rows, size_t *total)
{
    size_t a;
    size_t b;

    if (total == NULL || rows == 0 || rows == SIZE_MAX) {
        return 0;
    }

    a = rows;
    b = rows + 1;

    if ((a & (size_t)1) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > SIZE_MAX / a) {
        return 0;
    }

    *total = a * b;
    return 1;
}

static int maximum_path_sum(int64_t *triangle, size_t rows, int64_t *result)
{
    size_t total;
    size_t row_start;

    if (triangle == NULL || result == NULL ||
        !triangle_element_count(rows, &total)) {
        return 0;
    }

    row_start = total - rows;

    for (size_t row = rows - 1; row > 0; --row) {
        size_t parent_start = row_start - row;

        for (size_t column = 0; column < row; ++column) {
            int64_t left = triangle[row_start + column];
            int64_t right = triangle[row_start + column + 1];
            int64_t child = left > right ? left : right;
            int64_t sum;

            if (!add_checked(triangle[parent_start + column], child, &sum)) {
                return 0;
            }

            triangle[parent_start + column] = sum;
        }

        row_start = parent_start;
    }

    *result = triangle[0];
    return 1;
}

int main(void)
{
    size_t rows;
    size_t total;
    int64_t *triangle;
    int64_t result;

    if (!read_size(&rows) || rows == 0) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangle_element_count(rows, &total) ||
        total > SIZE_MAX / sizeof *triangle) {
        fputs("Triangle size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(total * sizeof *triangle);
    if (triangle == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < total; ++i) {
        if (!read_int64(&triangle[i])) {
            fputs("Invalid triangle element\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_path_sum(triangle, rows, &result)) {
        fputs("Unable to calculate maximum path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}