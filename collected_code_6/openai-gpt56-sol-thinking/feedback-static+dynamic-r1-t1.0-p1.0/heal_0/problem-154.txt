#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t row;
    size_t column;
} ElementPosition;

enum {
    EXTRACT_SUCCESS = 0,
    EXTRACT_INVALID_ARGUMENT = 1,
    EXTRACT_OUT_OF_BOUNDS = 2,
    EXTRACT_ALLOCATION_FAILURE = 3
};

int extract_elements(const int *matrix,
                     size_t rows,
                     size_t columns,
                     const ElementPosition *positions,
                     size_t position_count,
                     int **extracted)
{
    int *values;
    size_t i;

    if (extracted == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *extracted = NULL;

    if (matrix == NULL || rows == 0 || columns == 0 ||
        rows > SIZE_MAX / columns) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (position_count == 0) {
        return EXTRACT_SUCCESS;
    }

    if (positions == NULL || position_count > SIZE_MAX / sizeof(*values)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (i = 0; i < position_count; ++i) {
        if (positions[i].row >= rows ||
            positions[i].column >= columns) {
            return EXTRACT_OUT_OF_BOUNDS;
        }
    }

    values = malloc(position_count * sizeof(*values));
    if (values == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    for (i = 0; i < position_count; ++i) {
        values[i] = matrix[positions[i].row * columns +
                           positions[i].column];
    }

    *extracted = values;
    return EXTRACT_SUCCESS;
}

int main(void)
{
    size_t rows;
    size_t columns;
    size_t matrix_size;
    size_t position_count;
    size_t i;
    int *matrix = NULL;
    ElementPosition *positions = NULL;
    int *extracted = NULL;
    int status;
    int exit_status = EXIT_FAILURE;

    if (scanf("%zu %zu", &rows, &columns) != 2 ||
        rows == 0 || columns == 0 ||
        rows > SIZE_MAX / columns) {
        fputs("Invalid matrix dimensions\n", stderr);
        goto cleanup;
    }

    matrix_size = rows * columns;

    if (matrix_size > SIZE_MAX / sizeof(*matrix)) {
        fputs("Matrix is too large\n", stderr);
        goto cleanup;
    }

    matrix = malloc(matrix_size * sizeof(*matrix));
    if (matrix == NULL) {
        fputs("Unable to allocate matrix\n", stderr);
        goto cleanup;
    }

    for (i = 0; i < matrix_size; ++i) {
        if (scanf("%d", &matrix[i]) != 1) {
            fputs("Invalid matrix element\n", stderr);
            goto cleanup;
        }
    }

    if (scanf("%zu", &position_count) != 1) {
        fputs("Invalid position count\n", stderr);
        goto cleanup;
    }

    if (position_count > SIZE_MAX / sizeof(*positions)) {
        fputs("Position list is too large\n", stderr);
        goto cleanup;
    }

    if (position_count > 0) {
        positions = malloc(position_count * sizeof(*positions));
        if (positions == NULL) {
            fputs("Unable to allocate position list\n", stderr);
            goto cleanup;
        }
    }

    for (i = 0; i < position_count; ++i) {
        if (scanf("%zu %zu", &positions[i].row,
                  &positions[i].column) != 2) {
            fputs("Invalid position\n", stderr);
            goto cleanup;
        }
    }

    status = extract_elements(matrix, rows, columns, positions,
                              position_count, &extracted);
    if (status != EXTRACT_SUCCESS) {
        fputs("Unable to extract elements\n", stderr);
        goto cleanup;
    }

    for (i = 0; i < position_count; ++i) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", extracted[i]);
    }
    putchar('\n');

    if (ferror(stdout)) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(extracted);
    free(positions);
    free(matrix);
    return exit_status;
}