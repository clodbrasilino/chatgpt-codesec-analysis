#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void swapRows(int a[SIZE][SIZE], int row1, int row2, int col) {
    for (int i = 0; i < col; i++) {
        int temp = a[row1][i];
        a[row1][i] = a[row2][i];
        a[row2][i] = temp;
    }
}

int rowSum(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

void sortMatrix(int a[SIZE][SIZE], int m, int n) {
    for (int i = 0; i < m-1; i++) {
        for (int j = 0; j < m-i-1; j++) {
            if (rowSum(a[j], n) > rowSum(a[j + 1], n)) {
                swapRows(a, j, j+1, n);
            }
        }
    }
}

void printMatrix(int a[SIZE][SIZE], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[SIZE][SIZE] = {
        {5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5},
        {9, 10, 11, 12, 13},
        {0, 0, 0, 0, 0},
        {6, 7, 8, 9, 10}
    };

    sortMatrix(matrix, SIZE, SIZE);
    printMatrix(matrix, SIZE, SIZE);

    return 0;
}