#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double max(double a, double b) {
    return (a > b) ? a : b;
}

double findMaxAveragePath(int** matrix, int n, int x, int y, double sum, int steps, double** dp) {
    if (x < 0 || y < 0 || x >= n || y >= n) return -DBL_MAX;
    if (dp[x][y] != -1) return dp[x][y];
    sum += matrix[x][y];
    steps++;
    if (x == n-1 && y == n-1) {
        dp[x][y] = sum / steps;
        return dp[x][y];
    }
    double right = findMaxAveragePath(matrix, n, x, y+1, sum, steps, dp);
    double down = findMaxAveragePath(matrix, n, x+1, y, sum, steps, dp);
    double result = max(right, down);
    dp[x][y] = max(dp[x][y], result);
    return dp[x][y];
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5.2, got 3.7999999523162842
  *  test case 2 failed: expected 7.2, got 5.8000001907348633
  *  test case 1 failed: expected 6.2, got 4.8000001907348633
  */

double maxAveragePath(int** matrix, int n) {
    double** dp = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        dp[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    double result = findMaxAveragePath(matrix, n, 0, 0, 0, 0, dp);
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    double result = maxAveragePath(matrix, n);
    printf("%.2f\n", result);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}