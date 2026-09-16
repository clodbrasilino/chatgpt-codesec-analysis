#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int extract_column(const int *matrix, size_t rows, size_t columns,
                          size_t column, int **result)
{
    int *values;
    size_t row;

    if (matrix == NULL || result == NULL || rows == 0U ||
        columns == 0U || column >= columns ||
        rows > SIZE_MAX / sizeof(*values)) {
        return 0;
    }

    values = malloc(rows * sizeof(*values));
    if (values == NULL) {
        return 0;
    }

    for (row = 0U; row < rows; ++row) {
        values[row] = matrix[row * columns + column];
    }

    *result = values;
    return 1;
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
    const size_t column = 0U;
    int *result = NULL;
    size_t index;

    if (!extract_column(&matrix[0][0], rows, columns, column, &result)) {
        fputs("Unable to extract the specified elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < rows; ++index) {
        if (printf("%d%s", result[index], index + 1U < rows ? " " : "\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}