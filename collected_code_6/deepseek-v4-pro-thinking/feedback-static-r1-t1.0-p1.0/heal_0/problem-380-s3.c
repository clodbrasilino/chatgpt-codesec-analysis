#include <stdlib.h>
#include <stdio.h>

int **generate_2d_array(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    int **array = malloc((size_t)rows * sizeof(*array));
    if (array == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        array[i] = malloc((size_t)cols * sizeof(*array[i]));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = 0;
        }
    }

    return array;
}

void free_2d_array(int **array, int rows) {
    if (array == NULL) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

int main(void) {
    int rows = 3;
    int cols = 4;

    int **array = generate_2d_array(rows, cols);
    if (array == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    free_2d_array(array, rows);
    return 0;
}