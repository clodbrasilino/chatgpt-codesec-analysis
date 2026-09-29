#include <stdio.h>
#include <stdlib.h>

#define N 3

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minTotal(int triangle[N][N], int m, int n) {
    for (int i = m - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }
    return triangle[0][0];
}

int main() {
    int triangle[N][N] = { {2, 0, 0}, {3, 4, 0}, {6, 5, 7} };
    printf("Minimum Total Path Sum: %d\n", minTotal(triangle, N, N));
    return 0;
}