#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memset'
  */

#define N 3

void generateSquare(int n) {
    int magicSquare[n][n];

    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'memset' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'memset'
     *  implicit declaration of function 'memset' [-Wimplicit-function-declaration]
     */
    memset(magicSquare, 0, sizeof(magicSquare));

    int i = n / 2;
    int j = n - 1;

    for (int num = 1; num <= n * n;) {
        if (i == -1 && j == n)
        {
            j = n - 2;
            i = 0;
        }
        else{
            if (j == n)
                j = 0;
            if (i < 0)
                i = n - 1;
        }
        if (magicSquare[(int)i][(int)j]){
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[(int)i][(int)j] = num++;

        j++;
        i--;
    }

    printf("The Magic Square for n = %d is: \n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%3d ", magicSquare[i][j]);
        printf("\n");
    }
}

int main() {
    if (N % 2 == 0) {
        printf("Magic square only works with odd numbers\n");
        return 0;
    }
    generateSquare(N);
    return 0;
}