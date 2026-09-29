#include <stdio.h>
#include <stdlib.h>

int** create_2d_array(int rows, int cols) {
    int **array = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        array[i] = (int *)malloc(cols * sizeof(int));
    }
    return array;
}

void free_2d_array(int **array, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);
}

int* extract_elements(int **array, int rows, int cols, int step, int *result_size) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; j += step) {
            ++count;
        }
    }
    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; j += step) {
            result[index++] = array[i][j];
        }
    }
    *result_size = count;
    return result;
}

int main() {
    int rows = 3;
    int cols = 4;
    int step = 2;

    int **array = create_2d_array(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            array[i][j] = i * cols + j;
        }
    }

    int result_size;
    int *result = extract_elements(array, rows, cols, step, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    }

    free_2d_array(array, rows);
    return 0;
}