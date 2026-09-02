#include <stdio.h>
#include <stdlib.h>

void generateMagicSquare(int n, int magicSquare[n][n]) {
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     */
    int i, j, num = 1, row = 0, col = n / 2;

    for (i = 0; i < n * n; i++) {
        magicSquare[row][col] = num++;
        row--;
        col++;
        if (num % n == 0) {
            row += 2;
            col--;
        } else {
            if (row < 0) row = n - 1;
            if (col == n) col = 0;
        }
        if (magicSquare[row][col] != 0) {
            row += 2;
            col--;
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the magic square (odd number): ");
    scanf("%d", &n);

    if (n <= 0 || n % 2 == 0) {
        return 1;
    }

    int **magicSquare = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)malloc(n * sizeof(int));
    }

    generateMagicSquare(n, (int (*)[n])magicSquare);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d ", magicSquare[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);

    return 0;
}