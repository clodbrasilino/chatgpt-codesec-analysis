#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

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

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *start;
    char *end;
    int ch;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    if (buffer[0] != '\0' && buffer[sizeof(buffer) - 2] != '\n') {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    *value = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0';
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    if (buffer[0] != '\0' && buffer[sizeof(buffer) - 2] != '\n') {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
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

    if (!read_size(&rows) || rows == 0) {
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