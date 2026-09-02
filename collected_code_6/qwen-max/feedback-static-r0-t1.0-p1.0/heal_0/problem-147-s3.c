#include <stdio.h>
#include <stdlib.h>

int** createTriangle(int n, int* triangleSizes) {
    int** triangle = (int**)malloc(n * sizeof(int*));
    *triangleSizes = n;
    for (int i = 0; i < n; ++i) {
        triangle[i] = (int*)malloc((i + 1) * sizeof(int));
        for (int j = 0; j <= i; ++j) {
            scanf("%d", &triangle[i][j]);
        }
    }
    return triangle;
}

void freeTriangle(int** triangle, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(triangle[i]);
    }
    free(triangle);
}

int maxPathSum(int** triangle, int n) {
    for (int row = n - 2; row >= 0; --row) {
        for (int col = 0; col <= row; ++col) {
            triangle[row][col] += (triangle[row + 1][col] > triangle[row + 1][col + 1]) ? triangle[row + 1][col] : triangle[row + 1][col + 1];
        }
    }
    return triangle[0][0];
}

int main() {
    int n, triangleSize;
    scanf("%d", &n);
    int** triangle = createTriangle(n, &triangleSize);
    printf("%d\n", maxPathSum(triangle, triangleSize));
    freeTriangle(triangle, n);
    return 0;
}