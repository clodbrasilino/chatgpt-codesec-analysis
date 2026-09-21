#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int read_token(char *buffer, size_t size)
{
    int character;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        character = getchar();
        if (character == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)character));

    do {
        if (length + 1 >= size) {
            do {
                character = getchar();
            } while (character != EOF &&
                     !isspace((unsigned char)character));
            return 0;
        }

        buffer[length++] = (char)character;
        character = getchar();
    } while (character != EOF && !isspace((unsigned char)character));

    buffer[length] = '\0';
    return 1;
}

static int read_size_value(size_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char buffer[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
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

    if (triangle == NULL || maximum == NULL || rows == 0) {
        return 0;
    }

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        return 0;
    }

    element_count = rows * (rows + 1) / 2;

    if (rows > SIZE_MAX / sizeof(*sums)) {
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

    if (!read_size_value(&rows) || rows == 0) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        fputs("Triangle size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < element_count; ++index) {
        if (!read_int64_value(&triangle[index])) {
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