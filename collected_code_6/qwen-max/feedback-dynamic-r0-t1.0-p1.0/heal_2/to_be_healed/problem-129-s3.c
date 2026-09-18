#include <stdio.h>
#include <stdlib.h>

void initializeMagicSquare(int n, int square[][10]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            square[i][j] = 0;
        }
    }
}

int isMagicSquare(int n, int square[][10]) {
    int sumDiag1 = 0, sumDiag2 = 0, rowSum, colSum;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -727379971 * -727379971 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:4190,execs:2572,op:havoc,rep:14)
     * UBSan: signed integer overflow: -727379971 * -1524522998 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:4190,execs:2572,op:havoc,rep:14)
     */
    int expectedSum = n * (n * n + 1) / 2;

    for (int i = 0; i < n; ++i) {
        rowSum = 0;
        colSum = 0;
        for (int j = 0; j < n; ++j) {
            rowSum += square[i][j];
            colSum += square[j][i];
        }
        if (rowSum != expectedSum || colSum != expectedSum) {
            return 0;
        }
        sumDiag1 += square[i][i];
        sumDiag2 += square[i][n - 1 - i];
    }

    return (sumDiag1 == expectedSum && sumDiag2 == expectedSum);
}

void generateMagicSquare(int n, int square[][10]) {
    initializeMagicSquare(n, square);
    int i = n / 2, j = n - 1;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -727379971 * -727379971 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:4190,execs:2572,op:havoc,rep:14)
     */
    for (int num = 1; num <= n * n;) {
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
        /* Possible weaknesses found:
         * UBSan: index -4 out of bounds for type 'int[10]' (AFL crash: id:000003,sig:06,src:000008,time:21063,execs:11997,op:havoc,rep:8)
         * UBSan: index -6 out of bounds for type 'int[10]' (AFL crash: id:000002,sig:06,src:000000,time:9008,execs:5245,op:havoc,rep:9)
         */
        if (square[i][j]) {
            j -= 2;
            i++;
            continue;
        } else {
            /* Possible weaknesses found:
             * UBSan: index -28 out of bounds for type 'int[10]' (AFL crash: id:000003,sig:06,src:000008,time:21063,execs:11997,op:havoc,rep:8)
             * UBSan: index -8 out of bounds for type 'int[10]' (AFL crash: id:000002,sig:06,src:000000,time:9008,execs:5245,op:havoc,rep:9)
             */
            square[i][j] = num++;
        }
        j++;
        i--;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:616,execs:407,op:havoc,rep:9; likely memory-safety defect
  */

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