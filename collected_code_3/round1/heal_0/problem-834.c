#include <stdio.h>
#include <stdlib.h>

void generateSpiralMatrix(int n, int a[n][n]) {
    int value = 1;
    int row_start = 0, col_start = 0;
    int row_end = n - 1, col_end = n - 1;

    while (value <= n*n) {
        for (int i = col_start; i <= col_end; i++) {
            a[row_start][i] = value++;
        }
        for (int i = row_start + 1; i <= row_end; i++) {
            a[i][col_end] = value++;
        }
        for (int i = col_end - 1; i >= col_start; i--) {
            a[row_end][i] = value++;
        }
        for (int i = row_end - 1; i > row_start; i--) {
            a[i][col_start] = value++;
        }
        row_start++;
        row_end--;
        col_start++;
        col_end--;
    }
}

void printMatrix(int n, int a[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);
    int a[n][n];
    generateSpiralMatrix(n, a);
    printMatrix(n, a);
    return 0;
}