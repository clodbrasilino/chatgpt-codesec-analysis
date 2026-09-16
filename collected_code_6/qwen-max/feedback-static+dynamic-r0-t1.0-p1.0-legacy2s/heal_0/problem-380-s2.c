#include <stdio.h>
#include <stdlib.h>

int** generate_2d_array(int rows, int cols) {
    int **array;
    array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; ++i) {
        array[i] = (int *)calloc(cols, sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(array[j]);
            }
            free(array);
            exit(EXIT_FAILURE);
        }
    }
    return array;
}

void free_2d_array(int **array, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);
}

int main() {
    int rows = 3, cols = 4;
    int **array = generate_2d_array(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    free_2d_array(array, rows);
    return 0;
}