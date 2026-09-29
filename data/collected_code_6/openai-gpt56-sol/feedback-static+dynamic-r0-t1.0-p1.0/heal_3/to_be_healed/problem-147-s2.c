#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

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

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
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

    if ((a & 1U) == 0U) {
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

static int maximum_path_sum(const int64_t *triangle, size_t rows,
                            int64_t *result)
{
    int64_t *sums;
    size_t total;
    size_t row_start;

    if (triangle == NULL || result == NULL ||
        !triangle_element_count(rows, &total) ||
        total > SIZE_MAX / sizeof(*sums)) {
        return 0;
    }

    sums = malloc(total * sizeof(*sums));
    if (sums == NULL) {
        return 0;
    }

    for (size_t i = 0; i < total; ++i) {
        sums[i] = triangle[i];
    }

    row_start = total - rows;

    for (size_t row = rows - 1; row > 0; --row) {
        size_t parent_start = row_start - row;

        for (size_t column = 0; column < row; ++column) {
            int64_t left = sums[row_start + column];
            int64_t right = sums[row_start + column + 1];
            int64_t child = left > right ? left : right;

            if (!add_checked(sums[parent_start + column], child,
                             &sums[parent_start + column])) {
                free(sums);
                return 0;
            }
        }

        row_start = parent_start;
    }

    *result = sums[0];
    free(sums);
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
        total > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(total * sizeof(*triangle));
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