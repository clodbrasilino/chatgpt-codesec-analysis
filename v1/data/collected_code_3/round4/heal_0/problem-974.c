#include <stdio.h>
#include <stdlib.h>

#define N 3

int min(int x, int y);

int minTotal(int triangle[N][N], int m, int n) {
    if (m < 0 || m > n)
        return 0;
    else
        return triangle[m][n] + min(minTotal(triangle, m + 1, n), minTotal(triangle, m + 1, n + 1));
}

int min(int x, int y) {
    return (x < y)? x: y;
}

int main() {
    int triangle[N][N] = { {2, 0, 0},
                           {3, 4, 0},
                           {6, 5, 7} };

    printf("Minimum total path sum is %d ", minTotal(triangle, 0, 0));
    return 0;
}