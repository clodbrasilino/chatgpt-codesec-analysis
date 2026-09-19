#include <stdio.h>

void initializeMagicSquare(int n, int square[][10]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            square[i][j] = 0;
        }
    }
}

int isMagicSquare(int n, int square[][10]) {
    int sumDiag1 = 0, sumDiag2 = 0;

    for (int i = 0; i < n; ++i) {
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < n; ++j) {
            rowSum += square[i][j];
            colSum += square[j][i];
        }
        if (rowSum != n * (n * n + 1) / 2 || colSum != n * (n * n + 1) / 2) {
            return 0;
        }
        sumDiag1 += square[i][i];
        sumDiag2 += square[i][n - 1 - i];
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1000737679 * -403072542 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:7590,execs:3457,op:havoc,rep:12)
     * UBSan: signed integer overflow: -1000737679 * -1000737679 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:7590,execs:3457,op:havoc,rep:12)
     */
    return (sumDiag1 == n * (n * n + 1) / 2 && sumDiag2 == n * (n * n + 1) / 2);
}

void generateMagicSquare(int n, int square[][10]) {
    initializeMagicSquare(n, square);
    int i = n / 2, j = n - 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1000737679 * -1000737679 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:7590,execs:3457,op:havoc,rep:12)
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
         * UBSan: index -4 out of bounds for type 'int[10]' (AFL crash: id:000002,sig:06,src:000008,time:8550,execs:3853,op:havoc,rep:3)
         */
        if (square[i][j]) {
            j -= 2;
            i++;
            continue;
        } else {
            /* Possible weaknesses found:
             * UBSan: index -28 out of bounds for type 'int[10]' (AFL crash: id:000002,sig:06,src:000008,time:8550,execs:3853,op:havoc,rep:3)
             */
            square[i][j] = num++;
        }
        j++; 
        i--; 
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000008,time:7195,execs:3298,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the size of magic square (odd number): ");
    scanf("%d", &n);

    int magicSquare[10][10];

    if (n % 2 == 0 || n > 10) {
        printf("Invalid input. Size must be an odd number and less than or equal to 10.\n");
        return 1;
    }

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