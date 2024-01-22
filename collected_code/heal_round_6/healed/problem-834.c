#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void generateMatrix(int n) {
    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid input for matrix size.\n");
        return;
    }

    int matrix[MAX_SIZE][MAX_SIZE];
    int num = 1, row_start = 0, row_end = n - 1, col_start = 0, col_end = n - 1;

    while (num <= n * n && row_start <= row_end && col_start <= col_end) {
        for (int i = col_start; i <= col_end; ++i)
            matrix[row_start][i] = num++;
        row_start++;

        if (row_start > row_end) break;
    
        for (int i = row_start; i <= row_end; ++i)
            matrix[i][col_end] = num++;
        col_end--;

        if (col_start > col_end) break;

        for (int i = col_end; i >= col_start && row_start <= row_end; --i)
            matrix[row_end][i] = num++;
        row_end--;

        if (row_start > row_end) break;

        for (int i = row_end; i >= row_start && col_start <= col_end; --i)
            matrix[i][col_start] = num++;
        col_start++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main() {
    int n;

    printf("Enter the value of n between 1 and %d: ", MAX_SIZE);
    while(scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        while(getchar() != '\n');
        printf("Invalid entry. Please enter a positive integer: ");
    }

    generateMatrix(n);

    return 0;
}