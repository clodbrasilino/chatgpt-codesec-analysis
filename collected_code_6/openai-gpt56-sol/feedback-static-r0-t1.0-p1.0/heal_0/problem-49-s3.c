#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int extract_column(const int *matrix, size_t rows, size_t columns,
                          size_t column_index, int **result)
{
    int *values;
    size_t row;

    if (matrix == NULL || result == NULL || rows == 0 ||
        columns == 0 || column_index >= columns) {
        return -1;
    }

    if (rows > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    values = malloc(rows * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (row = 0; row < rows; ++row) {
        values[row] = matrix[row * columns + column_index];
    }

    *result = values;
    return 0;
}

int main(void)
{
    const int matrix[][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    const size_t rows = sizeof(matrix) / sizeof(matrix[0]);
    const size_t columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);
    const size_t column_index = 0;
    int *result = NULL;
    size_t index;

    if (extract_column(&matrix[0][0], rows, columns,
                       column_index, &result) != 0) {
        fputs("Unable to extract the requested elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < rows; ++index) {
        if (printf("%d%s", result[index], index + 1 == rows ? "\n" : " ") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}