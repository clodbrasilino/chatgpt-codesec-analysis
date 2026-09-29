#include <stdio.h>
#include <stdlib.h>

int** generate_2d_array(size_t rows, size_t cols);
void free_2d_array(int** array, size_t rows);

int** generate_2d_array(size_t rows, size_t cols) {
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
    }

    return array;
}

void free_2d_array(int** array, size_t rows) {
    if (array == NULL) {
        return;
    }
    for (size_t i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

int main(void) {
    size_t rows = 5;
    size_t cols = 4;

    int** my_array = generate_2d_array(rows, cols);
    if (my_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            my_array[i][j] = (int)(i * cols + j);
        }
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%2d ", my_array[i][j]);
        }
        printf("\n");
    }

    free_2d_array(my_array, rows);
    my_array = NULL;

    return EXIT_SUCCESS;
}