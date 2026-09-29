#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

static int read_line(char **buffer)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (length + 1 > capacity) {
        char *new_line = realloc(line, length + 1);

        if (new_line == NULL) {
            free(line);
            return -1;
        }

        line = new_line;
    }

    line[length] = '\0';
    *buffer = line;
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
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
        return -1;
    }

    while (isspace((unsigned char)*end)) {
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
    char *buffer;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
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

static int checked_triangle_elements(size_t rows, size_t *elements)
{
    size_t a;
    size_t b;

    if (elements == NULL || rows == 0 || rows == SIZE_MAX) {
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

    *elements = a * b;
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

static int maximum_path_sum(const int64_t *triangle, size_t rows,
                            int64_t *result)
{
    int64_t *sums;
    size_t elements;
    size_t offset;

    if (triangle == NULL || result == NULL ||
        checked_triangle_elements(rows, &elements) != 0 ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    offset = elements - rows;

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        offset = row * (row - 1) / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t best = sums[column] > sums[column + 1]
                               ? sums[column]
                               : sums[column + 1];

            if (checked_add_int64(triangle[offset + column], best,
                                  &sums[column]) != 0) {
                free(sums);
                return -1;
            }
        }
    }

    *result = sums[0];
    free(sums);
    return 0;
}

int main(void)
{
    size_t rows;
    size_t elements;
    int64_t *triangle;
    int64_t result;

    if (read_size(&rows) != 0 ||
        checked_triangle_elements(rows, &elements) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (elements > SIZE_MAX / sizeof(*triangle)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(elements * sizeof(*triangle));
    if (triangle == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < elements; ++i) {
        if (read_int64(&triangle[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (maximum_path_sum(triangle, rows, &result) != 0) {
        fputs("Unable to calculate path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(triangle);
    return EXIT_SUCCESS;
}