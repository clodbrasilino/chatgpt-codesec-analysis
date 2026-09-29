#include <stdio.h>
#include <stdlib.h>

void initializeMagicSquare(int n, int square[10][10]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            square[i][j] = 0;
        }
    }
}

int isMagicSquare(int n, int square[10][10]) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1780336413 * -1780336413 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:438,execs:276,op:havoc,rep:2)
     */
    long long expectedSum = (long long)n * (n * n + 1) / 2;

    for (int i = 0; i < n; ++i) {
        long long rowSum = 0, colSum = 0;
        for (int j = 0; j < n; ++j) {
            rowSum += square[i][j];
            colSum += square[j][i];
        }
        if (rowSum != expectedSum || colSum != expectedSum) {
            return 0;
        }
    }

    long long sumDiag1 = 0, sumDiag2 = 0;
    for (int i = 0; i < n; ++i) {
        sumDiag1 += square[i][i];
        sumDiag2 += square[i][n - 1 - i];
    }

    return (sumDiag1 == expectedSum && sumDiag2 == expectedSum);
}

void generateMagicSquare(int n, int square[10][10]) {
    initializeMagicSquare(n, square);
    int i = n / 2, j = n - 1;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1780336413 * -1780336413 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:438,execs:276,op:havoc,rep:2)
     */
    for (int num = 1; num <= n * n;) {
        if (i == -1 && j == n) {
            j = n - 2;
            i = 0;
        } else {
            if (j == n) j = 0;
            if (i < 0) i = n - 1;
        }

        if (i >= 0 && i < n && j >= 0 && j < n && square[i][j] != 0) {
            j -= 2;
            i++;
            if (i < 0) i = n - 1;
            if (j < 0) j = n - 1;
            continue;
        }

        /* Possible weaknesses found:
         * UBSan: index -4 out of bounds for type 'int[10]' (AFL crash: id:000003,sig:06,src:000005,time:57978,execs:31986,op:havoc,rep:3)
         * UBSan: index -10 out of bounds for type 'int[10]' (AFL crash: id:000002,sig:06,src:000006,time:15732,execs:9688,op:havoc,rep:13)
         * ASan: stack-buffer-overflow (AFL crash: id:000001,sig:06,src:000000,time:1340,execs:748,op:havoc,rep:2)
         * UBSan: index -2 out of bounds for type 'int[10]' (AFL crash: id:000001,sig:06,src:000000,time:1340,execs:748,op:havoc,rep:2)
         */
        square[i][j] = num++;
        j = (j + 1) % n;
        i = (i - 1 + n) % n;
    }
}

int main() {
    int n;
    printf("Enter the size of magic square (odd number): ");
    if (scanf("%d", &n) != 1 || n % 2 == 0 || n > 10) {
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