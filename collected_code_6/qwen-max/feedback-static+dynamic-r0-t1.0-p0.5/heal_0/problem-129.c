#include <stdio.h>
#include <stdlib.h>

int** createMagicSquare(int n, int* magicSum) {
    if (n < 3 || n % 2 == 0) return NULL;
    *magicSum = n * (n * n + 1) / 2;
    int** square = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        square[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            square[i][j] = 0;
        }
    }
    int row = n / 2, col = n - 1;
    for (int num = 1; num <= n * n; ++num) {
        if (row == -1 && col == n) { 
            row = 0;
            col = n - 2;
        } else {
            if (col == n) col = 0;
            if (row < 0) row = n - 1;
        }
        if (square[row][col]) {
            row = row + 1;
            col = col - 2;
            continue;
        } else {
            square[row][col] = num;
        }
        row--;
        col++;
    }
    return square;
}

void printMagicSquare(int** square, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d", square[i][j]);
        }
        printf("\n");
    }
}

void freeMagicSquare(int** square, int n) {
    for (int i = 0; i < n; ++i) {
        free(square[i]);
    }
    free(square);
}

int main() {
    int n = 3;
    int magicSum;
    int** magicSquare = createMagicSquare(n, &magicSum);
    if (magicSquare != NULL) {
        printMagicSquare(magicSquare, n);
        freeMagicSquare(magicSquare, n);
    } else {
        printf("Cannot generate magic square for this size.\n");
    }
    return 0;
}