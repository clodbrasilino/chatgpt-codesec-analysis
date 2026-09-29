#include <stdio.h>
#include <stdlib.h>

int *extract_column(const int *matrix, size_t rows, size_t cols, size_t index, size_t *out_len)
{
    int *result = NULL;
    size_t i;

    if (matrix == NULL || out_len == NULL || rows == 0U || cols == 0U || index >= cols) {
        return NULL;
    }

    result = malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < rows; i++) {
        result[i] = matrix[(i * cols) + index];
    }

    *out_len = rows;
    return result;
}

int main(void)
{
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    size_t len = 0U;
    size_t i;
    int *column = NULL;

    column = extract_column(&matrix[0][0], 3U, 4U, 2U, &len);
    if (column == NULL) {
        (void)fprintf(stderr, "Extraction failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < len; i++) {
        if (printf("%d ", column[i]) < 0) {
            free(column);
            return EXIT_FAILURE;
        }
    }
    (void)printf("\n");

    free(column);
    column = NULL;

    return EXIT_SUCCESS;
}