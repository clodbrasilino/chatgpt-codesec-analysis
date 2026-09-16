#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t row;
    size_t column;
} ElementPosition;

typedef enum {
    EXTRACT_SUCCESS,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_OUT_OF_BOUNDS,
    EXTRACT_ALLOCATION_FAILURE
} ExtractStatus;

ExtractStatus extract_elements(
    const int *matrix,
    size_t rows,
    size_t columns,
    const ElementPosition *positions,
    size_t position_count,
    int **extracted_values)
{
    int *values;
    size_t i;

    if (extracted_values == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *extracted_values = NULL;

    if (matrix == NULL || rows == 0 || columns == 0 ||
        rows > SIZE_MAX / columns ||
        rows * columns > SIZE_MAX / sizeof(*matrix)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (position_count == 0) {
        return EXTRACT_SUCCESS;
    }

    if (positions == NULL ||
        position_count > SIZE_MAX / sizeof(*values)) {
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

    *extracted_values = values;
    return EXTRACT_SUCCESS;
}

int main(void)
{
    const int matrix[][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    const ElementPosition positions[] = {
        {0, 1},
        {1, 3},
        {2, 0},
        {2, 2}
    };
    const size_t rows = sizeof(matrix) / sizeof(matrix[0]);
    const size_t columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);
    const size_t position_count = sizeof(positions) / sizeof(positions[0]);
    int *extracted_values = NULL;
    ExtractStatus status;
    size_t i;

    status = extract_elements(
        &matrix[0][0],
        rows,
        columns,
        positions,
        position_count,
        &extracted_values
    );

    if (status != EXTRACT_SUCCESS) {
        fprintf(stderr, "Element extraction failed with status %d\n", status);
        free(extracted_values);
        return EXIT_FAILURE;
    }

    for (i = 0; i < position_count; ++i) {
        printf("%d%s",
               extracted_values[i],
               i + 1 == position_count ? "\n" : " ");
    }

    free(extracted_values);
    return EXIT_SUCCESS;
}