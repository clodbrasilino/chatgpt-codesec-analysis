#include <stdio.h>
#include <stdlib.h>

int extract_column(const int *matrix, size_t rows, size_t cols, size_t index, int **result)
{
    size_t i;
    int *out;

    if (matrix == NULL || result == NULL) {
        return -1;
    }
    if (rows == 0 || cols == 0 || index >= cols) {
        return -1;
    }
    if (rows > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    out = malloc(rows * sizeof(int));
    if (out == NULL) {
        return -1;
    }

    for (i = 0; i < rows; i++) {
        out[i] = matrix[i * cols + index];
    }

    *result = out;
    return 0;
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    size_t index = 2;
    size_t i;
    int *extracted = NULL;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    if (extract_column(&matrix[0][0], rows, cols, index, &extracted) != 0) {
        fprintf(stderr, "Extraction failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        if (printf("%d\n", extracted[i]) < 0) {
            free(extracted);
            return EXIT_FAILURE;
        }
    }

    free(extracted);
    extracted = NULL;

    return EXIT_SUCCESS;
}