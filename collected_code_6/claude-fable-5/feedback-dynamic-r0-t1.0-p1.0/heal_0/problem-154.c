#include <stdio.h>
#include <stdlib.h>

int *extract_column(int **matrix, size_t rows, size_t cols, size_t index)
{
    int *result;
    size_t i;

    if (matrix == NULL || rows == 0 || index >= cols) {
        return NULL;
    }

    result = malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(result);
            return NULL;
        }
        result[i] = matrix[i][index];
    }

    return result;
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    size_t i;
    size_t j;
    int **matrix;
    int *column;
    int value = 1;

    matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        for (j = 0; j < cols; j++) {
            matrix[i][j] = value;
            value++;
        }
    }

    column = extract_column(matrix, rows, cols, 2);
    if (column == NULL) {
        for (i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        fprintf(stderr, "Extraction failed\n");
        return EXIT_FAILURE;
    }

    printf("Extracted column: ");
    for (i = 0; i < rows; i++) {
        printf("%d ", column[i]);
    }
    printf("\n");

    free(column);
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}