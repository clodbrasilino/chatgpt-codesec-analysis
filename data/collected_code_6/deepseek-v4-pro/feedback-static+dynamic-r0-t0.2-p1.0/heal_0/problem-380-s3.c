#include <stdio.h>
#include <stdlib.h>

int **generate_2d_array(int rows, int cols) {
    int **array;
    int i, j;

    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        array[i] = (int *)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            array[i][j] = i * cols + j;
        }
    }

    return array;
}

void free_2d_array(int **array, int rows) {
    int i;

    if (array == NULL) {
        return;
    }

    for (i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

int main(void) {
    int rows = 3;
    int cols = 4;
    int **array;
    int i, j;

    array = generate_2d_array(rows, cols);
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    free_2d_array(array, rows);
    return 0;
}