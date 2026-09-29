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

static int read_token(char **token)
{
    char *buffer;
    size_t capacity = 32;
    size_t length = 0;
    int character;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        character = fgetc(stdin);
        if (character == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)character));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (character != EOF && !isspace((unsigned char)character)) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size_value(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' ||
        buffer[0] == '-' ||
        !isdigit((unsigned char)buffer[0])) {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    size_t digit_index;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    digit_index = (buffer[0] == '+' || buffer[0] == '-') ? 1U : 0U;

    if (buffer[digit_index] == '\0' ||
        !isdigit((unsigned char)buffer[digit_index])) {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        *end != '\0' ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int calculate_element_count(size_t rows, size_t *count)
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

static int maximum_triangle_sum(const int64_t *triangle,
                                size_t rows,
                                int64_t *maximum)
{
    int64_t *sums;
    size_t element_count;
    size_t row;
    size_t column;
    size_t offset;

    if (triangle == NULL ||
        maximum == NULL ||
        !calculate_element_count(rows, &element_count) ||
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

            if (!add_checked(triangle[offset + column],
                             child,
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

    if (!calculate_element_count(rows, &element_count) ||
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