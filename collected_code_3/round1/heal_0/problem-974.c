#include <stdio.h>
#include <stdlib.h>

#define N 3

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minTotalPathSum(int triangle[N][N]) {
    int minPath[N][N];
    int i, j;

    minPath[0][0] = triangle[0][0];

    for (i = 1; i < N; i++) {
        minPath[i][0] = minPath[i-1][0] + triangle[i][0];
        minPath[i][i] = minPath[i-1][i-1] + triangle[i][i];
    }

    for (i = 2; i < N; i++) {
        for (j = 1; j < i; j++) {
            minPath[i][j] = min(minPath[i-1][j-1], minPath[i-1][j]) + triangle[i][j];
        }
    }

    int minTotal = minPath[N-1][0];
    for (i = 1; i < N; i++) {
        minTotal = min(minTotal, minPath[N-1][i]);
    }

    return minTotal;
}

int main() {
    int triangle[N][N] = {{2, 0, 0}, {3, 4, 0}, {6, 5, 7}};
    printf("Minimum Total Path Sum: %d\n", minTotalPathSum(triangle));
    return 0;
}