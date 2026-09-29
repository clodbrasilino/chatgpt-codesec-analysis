#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t row;
    size_t column;
} Position;

typedef struct {
    size_t rows;
    size_t columns;
    const int *data;
} IntMatrix;

typedef enum {
    EXTRACT_SUCCESS,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_OUT_OF_BOUNDS,
    EXTRACT_INSUFFICIENT_CAPACITY
} ExtractStatus;

ExtractStatus extract_elements(const IntMatrix *matrix,
                               const Position *positions,
                               size_t position_count,
                               int *output,
                               size_t output_capacity)
{
    size_t i;

    if (matrix == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (position_count == 0) {
        return EXTRACT_SUCCESS;
    }

    if (positions == NULL || output == NULL || matrix->data == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (matrix->rows == 0 || matrix->columns == 0 ||
        matrix->rows > SIZE_MAX / matrix->columns) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (output_capacity < position_count) {
        return EXTRACT_INSUFFICIENT_CAPACITY;
    }

    for (i = 0; i < position_count; ++i) {
        if (positions[i].row >= matrix->rows ||
            positions[i].column >= matrix->columns) {
            return EXTRACT_OUT_OF_BOUNDS;
        }
    }

    for (i = 0; i < position_count; ++i) {
        output[i] = matrix->data[
            positions[i].row * matrix->columns + positions[i].column
        ];
    }

    return EXTRACT_SUCCESS;
}

int main(void)
{
    const int matrix_data[] = {
        10, 20, 30, 40,
        50, 60, 70, 80,
        90, 100, 110, 120
    };
    const IntMatrix matrix = {
        3,
        4,
        matrix_data
    };
    const Position positions[] = {
        {0, 1},
        {1, 3},
        {2, 0},
        {2, 2}
    };
    int extracted[sizeof(positions) / sizeof(positions[0])];
    const size_t position_count = sizeof(positions) / sizeof(positions[0]);
    ExtractStatus status;
    size_t i;

    status = extract_elements(&matrix,
                              positions,
                              position_count,
                              extracted,
                              sizeof(extracted) / sizeof(extracted[0]));

    if (status != EXTRACT_SUCCESS) {
        if (fprintf(stderr, "Element extraction failed with status %d\n",
                    (int)status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < position_count; ++i) {
        if (printf("%d%s", extracted[i],
                   i + 1 == position_count ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}