#include <stdio.h>
#include <stdlib.h>

int** generate2DArray(size_t rows, size_t cols);
void free2DArray(int** array, size_t rows);

int** generate2DArray(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    int** array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        array[i] = (int*)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
        for (size_t j = 0; j < cols; j++) {
            array[i][j] = 0;
        }
    }

    return array;
}

void free2DArray(int** array, size_t rows) {
    if (array != NULL) {
        for (size_t i = 0; i < rows; i++) {
            free(array[i]);
        }
        free(array);
    }
}

int main(void) {
    size_t rows = 4;
    size_t cols = 5;

    int** my2DArray = generate2DArray(rows, cols);
    if (my2DArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", my2DArray[i][j]);
        }
        printf("\n");
    }

    free2DArray(my2DArray, rows);

    return EXIT_SUCCESS;
}