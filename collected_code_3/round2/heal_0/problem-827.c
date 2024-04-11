#include <stdio.h>

int sumColumn(int **list, int rows, int col) {
    int sum = 0;
    for(int i = 0; i < rows; i++) {
        sum += list[i][col];
    }
    return sum;
}

int main() {
    int rows = 3;
    int cols = 3;
    int **list = (int **)malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; i++) {
        list[i] = (int *)malloc(cols * sizeof(int));
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            list[i][j] = i + j;
        }
    }

    int colToSum = 1;
    int sum = sumColumn(list, rows, colToSum);
    printf("Sum of column %d is %d\n", colToSum, sum);

    for(int i = 0; i < rows; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}