#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity < 2) {
        char *buffer = malloc(64);

        if (buffer == NULL) {
            return -1;
        }

        free(*line);
        *line = buffer;
        *capacity = 64;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity = *capacity;
            char *temporary;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity *= 2;
                }

                if (new_capacity < required) {
                    return -1;
                }
            }

            temporary = realloc(*line, new_capacity);
            if (temporary == NULL) {
                return -1;
            }

            *line = temporary;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    (*line)[length] = '\0';
    return 0;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    size_t capacity = 0;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    start = line;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    size_t capacity = 0;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    start = line;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static int triangle_element_count(size_t rows, size_t *elements)
{
    size_t a;
    size_t b;

    if (elements == NULL || rows == 0 || rows == SIZE_MAX) {
        return -1;
    }

    a = rows;
    b = rows + 1;

    if ((a & (size_t)1) == 0) {
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
        triangle_element_count(rows, &elements) != 0 ||
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
        offset -= row;

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
        triangle_element_count(rows, &elements) != 0) {
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

    if (printf("%" PRId64 "\n", result) < 0) {
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);
    return EXIT_SUCCESS;
}