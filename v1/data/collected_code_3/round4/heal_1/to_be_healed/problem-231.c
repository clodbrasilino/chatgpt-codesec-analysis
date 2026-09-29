#include <stdio.h>
#define N 3

int maxSum(int tri[N][N]) {
    for (int i=N-1; i>=0; i--) {
        for (int j=0; j<=i; j++) {
            /* Possible weaknesses found:
             *  use of uninitialized value '*tri_46(D) + _3[j]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             *  read of 4 bytes from after the end of 'tri'
             *  valid subscripts for 'tri' are '[0]' to '[2]'
             *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
             */
            if (tri[i+1][j] > tri[i+1][j+1])
                tri[i][j] += tri[i+1][j];
            else
                tri[i][j] += tri[i+1][j+1];
        }
    }
    return tri[0][0];
}

int main() {
    int tri[N][N] = { {1, 0, 0},
                      {4, 8, 0},
                      {1, 5, 3} };
    printf("%d\n", maxSum(tri));
    return 0;
}