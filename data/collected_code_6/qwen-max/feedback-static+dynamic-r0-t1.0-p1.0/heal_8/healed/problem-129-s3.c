#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void initializeMagicSquare(int n, int square[10][10]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            square[i][j] = 0;
        }
    }
}

bool isMagicSquare(int n, int square[10][10]) {
    int64_t expectedSum = (int64_t)n * (n * n + 1) / 2;
    int64_t sumDiag1 = 0, sumDiag2 = 0;

    for (int i = 0; i < n; ++i) {
        int64_t rowSum = 0, colSum = 0;
        for (int j = 0; j < n; ++j) {
            rowSum += square[i][j];
            colSum += square[j][i];
        }
        if (rowSum != expectedSum || colSum != expectedSum) {
            return false;
        }
        sumDiag1 += square[i][i];
        sumDiag2 += square[i][n - 1 - i];
    }

    return (sumDiag1 == expectedSum && sumDiag2 == expectedSum);
}

void generateMagicSquare(int n, int square[10][10]) {
    initializeMagicSquare(n, square);
    int i = n / 2, j = n - 1;

    for (int num = 1; num <= n * n; ) {
        if (i == -1 && j == n) {
            j = n - 2;
            i = 0;
        } else {
            if (j == n) {
                j = 0;
            }
            if (i < 0) {
                i = n - 1;
            }
        }

        if (square[(i + n) % n][(j + n) % n] != 0) {
            j -= 2;
            i++;
            if (i >= n) i -= n;
            if (j < 0) j += n;
            continue;
        }

        square[i][j] = num++;
        j++; 
        i--; 
        if (j >= n) j -= n;
        if (i < 0) i += n;
    }
}

int main() {
    int n;
    printf("Enter the size of magic square (odd number): ");
    scanf("%d", &n);

    if (n % 2 == 0 || n > 10) {
        printf("Invalid input. Size must be an odd number and less than or equal to 10.\n");
        return 1;
    }

    int magicSquare[10][10];
    generateMagicSquare(n, magicSquare);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%3d ", magicSquare[i][j]);
        }
        printf("\n");
    }

    if (isMagicSquare(n, magicSquare)) {
        printf("The generated square is a magic square.\n");
    } else {
        printf("The generated square is not a magic square.\n");
    }

    return 0;
}