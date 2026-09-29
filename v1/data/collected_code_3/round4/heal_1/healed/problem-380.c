#include <stdio.h>
#include <stdlib.h>

int** generate2DArray(int rows, int cols) {
    int **array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        return NULL;
    }

    for(int i=0; i<rows; i++) {
        array[i] = (int *)malloc(cols * sizeof(int));
        if(array[i] == NULL) {
            for(int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            array[i][j] = i + j;
        }
    }

    return array;
}

int main() {
    int rows = 5, cols = 5;
    int **array = generate2DArray(rows, cols);

    if (array == NULL) {
        return 1;
    }

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<rows; i++) {
        free(array[i]);
    }
    free(array);
    
    return 0;
}