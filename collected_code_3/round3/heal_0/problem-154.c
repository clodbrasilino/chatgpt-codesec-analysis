#include <stdio.h>
#include <stdlib.h>

void extractElements(int **arr, int rows, int cols, int k) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if((i * cols + j + 1) % k == 0) {
                printf("%d ", arr[i][j]);
            }
        }
    }
    printf("\n");
}

int main() {
    int rows = 3, cols = 3, k = 2;
    int **arr = (int **)malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(cols * sizeof(int));
        for(int j = 0; j < cols; j++) {
            arr[i][j] = i * cols + j + 1;
        }
    }

    extractElements(arr, rows, cols, k);

    for(int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}