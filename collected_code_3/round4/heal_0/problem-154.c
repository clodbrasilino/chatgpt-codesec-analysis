#include <stdio.h>
#include <stdlib.h>

int* extractElements(int** arr, int rows, int cols, int k, int* size) {
    int* result = (int*)malloc(rows * cols * sizeof(int));
    *size = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if((i * cols + j + 1) % k == 0) {
                result[(*size)++] = arr[i][j];
            }
        }
    }
    return result;
}

int main() {
    int rows = 3, cols = 3, k = 2;
    int** arr = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        arr[i] = (int*)malloc(cols * sizeof(int));
        for(int j = 0; j < cols; j++) {
            arr[i][j] = i * cols + j + 1;
        }
    }
    int size;
    int* result = extractElements(arr, rows, cols, k, &size);
    for(int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    free(result);
    for(int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}