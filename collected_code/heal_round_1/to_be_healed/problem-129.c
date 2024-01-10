#include <stdio.h>

#define SIZE 15

void generateMagicSquare(int square[][SIZE], int n) {
    int row = 0, col = n / 2, num = 1;

    while (num <= n * n) {
        square[row][col] = num++;
        row--;
        col++;

        if (row < 0 && col == n) {
            row = 1;
            col = n - 1;
        } else if (row < 0) {
            row = n - 1;
        } else if (col == n) {
            col = 0;
        } else if (square[row][col] != 0) {
            row += 2;
            col--;
        }
    }
}

void printMagicSquare(int square[][SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'square[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%3d ", square[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of magic square (odd number): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    int square[SIZE][SIZE] = {0};

    generateMagicSquare(square, n);
    
    printf("\nMagic Square:\n");
    printMagicSquare(square, n);

    return 0;
}