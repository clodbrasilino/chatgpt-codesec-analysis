#include <stdio.h>
#include <stdlib.h>

int *extract_column(int **matrix, size_t rows, size_t cols, size_t index, size_t *out_count)
{
    int *result;
    size_t i;

    if (matrix == NULL || out_count == NULL || rows == 0 || index >= cols) {
        return NULL;
    }

    result = malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        result[i] = matrix[i][index];
    }

    *out_count = rows;
    return result;
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    size_t i;
    size_t j;
    size_t count = 0;
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
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
        for (j = 0; j < cols; j++) {
            matrix[i][j] = value;
            value++;
        }
    }

    column = extract_column(matrix, rows, cols, 0, &count);
    if (column == NULL) {
        fprintf(stderr, "Extraction failed\n");
        for (i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return EXIT_FAILURE;
    }

    printf("First elements: ");
    for (i = 0; i < count; i++) {
        printf("%d ", column[i]);
    }
    printf("\n");
    free(column);

    column = extract_column(matrix, rows, cols, 2, &count);
    if (column == NULL) {
        fprintf(stderr, "Extraction failed\n");
        for (i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return EXIT_FAILURE;
    }

    printf("Elements at index 2: ");
    for (i = 0; i < count; i++) {
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