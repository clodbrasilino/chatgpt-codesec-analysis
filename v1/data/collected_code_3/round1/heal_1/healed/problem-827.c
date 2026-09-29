#include <stdio.h>
#include <stdlib.h>

int sum_column(int **matrix, int rows, int column) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += matrix[i][column];
    }
    return sum;
}

int main() {
    int rows = 3;
    int cols = 3;

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if(!matrix) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if(!matrix[i]) {
            for(int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
    matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 9;

    int column_to_sum = 1;
    int sum = sum_column(matrix, rows, column_to_sum);
    printf("Sum of column %d is %d\n", column_to_sum, sum);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}