#include <stdio.h>
#include <stdlib.h>

int *extract_elements(int **matrix, int rows, int cols, int target, int *result_size) {
    if (matrix == NULL || result_size == NULL || rows <= 0 || cols <= 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == target) {
                    count++;
                }
            }
        }
    }

    *result_size = count;
    if (count == 0) {
        return NULL;
    }

    int *result = malloc(count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == target) {
                    result[index] = matrix[i][j];
                    index++;
                }
            }
        }
    }

    return result;
}

int main(void) {
    int rows = 3;
    int cols = 3;

    int **matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 4; matrix[1][1] = 2; matrix[1][2] = 5;
    matrix[2][0] = 6; matrix[2][1] = 7; matrix[2][2] = 2;

    int target = 2;
    int result_size = 0;
    int *result = extract_elements(matrix, rows, cols, target, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}