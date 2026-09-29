#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        buffer[0] = '\0';
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1) {
            do {
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));

            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[sizeof(uintmax_t) * CHAR_BIT + 2];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    if (buffer[0] == '+' || buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        end == NULL ||
        *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[sizeof(intmax_t) * CHAR_BIT + 3];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        end == NULL ||
        *end != '\0' ||
        parsed < (intmax_t)INT64_MIN ||
        parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int triangular_count(size_t rows, size_t *count)
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

    if (b != 0 && a > SIZE_MAX / b) {
        return 0;
    }

    *count = a * b;
    return 1;
}

static int row_offset(size_t row, size_t *offset)
{
    size_t a = row;
    size_t b;

    if (offset == NULL) {
        return 0;
    }

    b = row == 0 ? 0 : row - 1;

    if ((a & (size_t)1) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (b != 0 && a > SIZE_MAX / b) {
        return 0;
    }

    *offset = a * b;
    return 1;
}

static int maximum_path_sum(const int64_t *triangle, size_t rows,
                            int64_t *result)
{
    int64_t *sums;
    size_t last_row_start;

    if (triangle == NULL ||
        result == NULL ||
        rows == 0 ||
        rows > SIZE_MAX / sizeof(*sums) ||
        !row_offset(rows, &last_row_start)) {
        return 0;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return 0;
    }

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[last_row_start + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t start;

        if (!row_offset(row, &start)) {
            free(sums);
            return 0;
        }

        for (size_t column = 0; column < row; ++column) {
            int64_t best_child = sums[column] > sums[column + 1]
                               ? sums[column]
                               : sums[column + 1];

            if (!add_int64(triangle[start + column],
                           best_child,
                           &sums[column])) {
                free(sums);
                return 0;
            }
        }
    }

    *result = sums[0];
    free(sums);
    return 1;
}

int main(void)
{
    size_t rows;
    size_t element_count;
    int64_t *triangle;
    int64_t result;

    if (!read_size(&rows) ||
        !triangular_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (!read_int64(&triangle[index])) {
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_path_sum(triangle, rows, &result)) {
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}