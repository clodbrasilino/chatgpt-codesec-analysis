#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3

void sort_matrix(int matrix[ROWS][COLS]) {
    int row_sums[ROWS] = {0};
    int temp_row[COLS], temp_sum;

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            row_sums[i] += matrix[i][j];
        }
    }

    for(int i = 0; i < ROWS - 1; i++) {
        for(int j = i + 1; j < ROWS; j++) {
            if(row_sums[i] > row_sums[j]) {
                temp_sum = row_sums[i];
                row_sums[i] = row_sums[j];
                row_sums[j] = temp_sum;

                for(int k = 0; k < COLS; k++) {
                    temp_row[k] = matrix[i][k];
                    matrix[i][k] = matrix[j][k];
                    matrix[j][k] = temp_row[k];
                }
            }
        }
    }
}

int main() {
    int matrix[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    sort_matrix(matrix);

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}