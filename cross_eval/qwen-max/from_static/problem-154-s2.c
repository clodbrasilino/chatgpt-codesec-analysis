#include <stdio.h>
#include <stdlib.h>

void extract_elements(int **array, int rows, int cols, int interval, int *output) {
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j += interval) {
            output[index++] = array[i][j];
        }
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    int interval = 2;

    int **array = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        array[i] = (int *)malloc(cols * sizeof(int));
    }

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = k++;
        }
    }

    int output_len = (cols + interval - 1) / interval * rows;
    int *output = (int *)malloc(output_len * sizeof(int));

    extract_elements(array, rows, cols, interval, output);

    for (int i = 0; i < output_len; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
    free(output);

    return 0;
}