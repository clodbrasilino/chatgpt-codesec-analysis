#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list, int rows, int cols, int col_index) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += list[i][col_index];
    }
    return sum;
}

int main() {
    int rows = 3;
    int cols = 4;
    int **list = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        list[i] = (int *)malloc(cols * sizeof(int));
    }

    list[0][0] = 1; list[0][1] = 2; list[0][2] = 3; list[0][3] = 4;
    list[1][0] = 5; list[1][1] = 6; list[1][2] = 7; list[1][3] = 8;
    list[2][0] = 9; list[2][1] = 10; list[2][2] = 11; list[2][3] = 12;

    int col_index = 2;
    int result = sum_column(list, rows, cols, col_index);
    printf("Sum of column %d: %d\n", col_index, result);

    for (int i = 0; i < rows; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}