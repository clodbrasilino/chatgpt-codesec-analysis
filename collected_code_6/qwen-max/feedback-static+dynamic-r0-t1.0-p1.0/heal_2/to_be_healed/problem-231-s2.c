#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int** createTriangle(int n, const int input[]) {
    int **triangle = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        triangle[i] = (int*)malloc((i + 1) * sizeof(int));
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] = input[(i * (i + 1)) / 2 + j];
        }
    }
    return triangle;
}

void freeTriangle(int** triangle, int n) {
    for (int i = 0; i < n; ++i) {
        free(triangle[i]);
    }
    free(triangle);
}

int maxSumRightTriangle(int** triangle, int n) {
    for (int row = n - 2; row >= 0; --row) {
        for (int col = 0; col <= row; ++col) {
            triangle[row][col] += (triangle[row + 1][col] > triangle[row + 1][col + 1] ? triangle[row + 1][col] : triangle[row + 1][col + 1]);
        }
    }
    return triangle[0][0];
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    long long size = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (size > INT_MAX) {
        return 1;
    }
    int *input = (int*)malloc(size * sizeof(int));
    if (input == NULL) {
        return 1;
    }
    for (int i = 0; i < size; ++i) {
        if (scanf("%d", &input[i]) != 1) {
            free(input);
            return 1;
        }
    }

    int **triangle = createTriangle(n, input);
    int max_sum = maxSumRightTriangle(triangle, n);
    printf("%d\n", max_sum);

    free(input);
    freeTriangle(triangle, n);
    return 0;
}