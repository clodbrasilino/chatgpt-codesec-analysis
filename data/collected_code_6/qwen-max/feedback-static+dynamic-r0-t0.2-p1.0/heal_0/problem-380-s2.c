#include <stdio.h>
#include <stdlib.h>

int** create_2d_array(int rows, int cols) {
    int **array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; ++i) {
        array[i] = (int *)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(array[j]);
            }
            free(array);
            return NULL;
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
    int rows = 3;
    int cols = 4;
    int **myArray = create_2d_array(rows, cols);
    if (myArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            myArray[i][j] = i * cols + j;
            printf("%d ", myArray[i][j]);
        }
        printf("\n");
    }

    free_2d_array(myArray, rows);
    return 0;
}