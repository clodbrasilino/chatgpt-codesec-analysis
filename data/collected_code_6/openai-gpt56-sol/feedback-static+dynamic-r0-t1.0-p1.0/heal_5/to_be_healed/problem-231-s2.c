#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = 64;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *replacement;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(buffer);
                return 0;
            }

            replacement = realloc(buffer, new_capacity);
            if (replacement == NULL) {
                free(buffer);
                return 0;
            }

            buffer = replacement;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
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
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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

static int triangle_element_count(size_t rows, size_t *count)
{
    size_t a;
    size_t b;

    if (count == NULL || rows == 0 || rows == SIZE_MAX) {
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

    *count = a * b;
    return 1;
}

static int maximum_triangle_sum(const int64_t *triangle, size_t rows,
                                int64_t *maximum)
{
    int64_t *sums;
    size_t element_count;
    size_t row;
    size_t column;
    size_t offset;

    if (triangle == NULL || maximum == NULL ||
        !triangle_element_count(rows, &element_count) ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return 0;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return 0;
    }

    offset = element_count - rows;

    for (column = 0; column < rows; ++column) {
        sums[column] = triangle[offset + column];
    }

    for (row = rows - 1; row > 0; --row) {
        offset -= row;

        for (column = 0; column < row; ++column) {
            int64_t child = sums[column] > sums[column + 1]
                                ? sums[column]
                                : sums[column + 1];

            if (!add_checked(triangle[offset + column], child,
                             &sums[column])) {
                free(sums);
                return 0;
            }
        }
    }

    *maximum = sums[0];
    free(sums);
    return 1;
}

int main(void)
{
    size_t rows;
    size_t element_count;
    size_t index;
    int64_t *triangle;
    int64_t maximum;

    if (!read_size(&rows) || rows == 0) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangle_element_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < element_count; ++index) {
        if (!read_int64(&triangle[index])) {
            fputs("Invalid triangle data\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_triangle_sum(triangle, rows, &maximum)) {
        fputs("Unable to calculate maximum sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        fputs("Output error\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);
    return EXIT_SUCCESS;
}