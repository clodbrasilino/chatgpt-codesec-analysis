#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list, int rows, int cols, int col_index) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        sum += list[i][col_index];
    }
    return sum;
}

int main() {
    int rows = 3;
    int cols = 4;

    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     *  variable-sized object may not be initialized
     */
    int data[rows][cols] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int **list = (int **)malloc(rows * sizeof(int *));
    if (list == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; ++i) {
        list[i] = (int *)malloc(cols * sizeof(int));
        if (list[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(list[j]);
            }
            free(list);
            return 1;
        }
        for (int j = 0; j < cols; ++j) {
            list[i][j] = data[i][j];
        }
    }

    int col_index = 2;
    int result = sum_column(list, rows, cols, col_index);
    printf("Sum of column %d: %d\n", col_index, result);

    for (int i = 0; i < rows; ++i) {
        free(list[i]);
    }
    free(list);

    return 0;
}