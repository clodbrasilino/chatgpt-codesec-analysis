#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list, int row_count, int col_index) {
    int sum = 0;
    for (int i = 0; i < row_count; i++) {
        sum += list[i][col_index];
    }
    return sum;
}

int main() {
    int row_count = 3;
    int col_count = 4;
    int **list = (int **)malloc(row_count * sizeof(int *));
    for (int i = 0; i < row_count; i++) {
        list[i] = (int *)malloc(col_count * sizeof(int));
    }

    int values[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            list[i][j] = values[i][j];
        }
    }

    int col_index = 2;
    int result = sum_column(list, row_count, col_index);
    printf("Sum of column %d is: %d\n", col_index, result);

    for (int i = 0; i < row_count; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}