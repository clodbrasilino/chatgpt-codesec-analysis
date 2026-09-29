#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int findMaxTotal(int **triangle, int n) {
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] += MAX(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }
    return triangle[0][0];
}

int main() {
    int n;
    scanf("%d", &n);
    int **triangle = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
        for (int j = 0; j <= i; ++j) {
            scanf("%d", &triangle[i][j]);
        }
    }
    printf("%d\n", findMaxTotal(triangle, n));
    for (int i = 0; i < n; ++i) {
        free(triangle[i]);
    }
    free(triangle);
    return 0;
}