#include <stdio.h>
#include <stdlib.h>

int **generate_2d_array(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    int **arr = malloc(rows * sizeof(int *));
    if (arr == NULL) {
        return NULL;
    }

    int *data = malloc(rows * cols * sizeof(int));
    if (data == NULL) {
        free(arr);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        arr[i] = data + (i * cols);
    }

    for (size_t i = 0; i < rows * cols; i++) {
        data[i] = (int)i;
    }

    return arr;
}

void free_2d_array(int **arr) {
    if (arr != NULL) {
        free(arr[0]);
        free(arr);
    }
}

int main(void) {
    size_t rows = 4;
    size_t cols = 5;

    int **arr = generate_2d_array(rows, cols);
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    free_2d_array(arr);

    return EXIT_SUCCESS;
}