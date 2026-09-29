#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int column_max(const int *values, size_t rows, size_t columns,
                      size_t column, int *result)
{
    size_t row;
    int maximum;

    if (values == NULL || result == NULL || rows == 0U ||
        columns == 0U || column >= columns) {
        return -1;
    }

    maximum = values[column];

    for (row = 1U; row < rows; ++row) {
        int value = values[row * columns + column];

        if (value > maximum) {
            maximum = value;
        }
    }

    *result = maximum;
    return 0;
}

static int parse_size(const char *text, size_t *result)
{
    char *end = NULL;
    unsigned long long value;

    if (text == NULL || result == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    value = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value == 0ULL ||
        value > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *result = (size_t)value;
    return 0;
}

int main(int argc, char *argv[])
{
    int *tuples = NULL;
    int maximum;
    size_t rows;
    size_t columns;
    size_t column;
    size_t count;
    size_t index;
    int status = EXIT_FAILURE;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <rows> <columns> <column>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_size(argv[1], &rows) != 0 ||
        parse_size(argv[2], &columns) != 0 ||
        parse_size(argv[3], &column) != 0) {
        fprintf(stderr, "Invalid dimensions or column number\n");
        return EXIT_FAILURE;
    }

    if (column > columns || rows > SIZE_MAX / columns) {
        fprintf(stderr, "Dimensions are out of range\n");
        return EXIT_FAILURE;
    }

    count = rows * columns;

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (index = 0U; index < count; ++index) {
        if (scanf("%d", &tuples[index]) != 1) {
            fprintf(stderr, "Failed to read tuple data\n");
            goto cleanup;
        }
    }

    if (column_max(tuples, rows, columns, column - 1U, &maximum) != 0) {
        fprintf(stderr, "Failed to calculate maximum\n");
        goto cleanup;
    }

    if (printf("%d\n", maximum) < 0) {
        fprintf(stderr, "Failed to write output\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}