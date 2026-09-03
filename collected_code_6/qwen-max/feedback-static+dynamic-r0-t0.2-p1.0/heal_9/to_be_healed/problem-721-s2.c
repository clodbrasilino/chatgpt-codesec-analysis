#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double max(double a, double b) {
    return (a > b) ? a : b;
}

double findMaxAveragePath(int** matrix, int n, int x, int y, double sum, int steps, double** dp) {
    if (x >= n || y >= n) return -DBL_MAX;
    if (dp[x][y] != -1.0) return dp[x][y];
    sum += matrix[x][y];
    steps++;
    double right = (y + 1 < n) ? findMaxAveragePath(matrix, n, x, y + 1, sum, steps, dp) : -DBL_MAX;
    double down = (x + 1 < n) ? findMaxAveragePath(matrix, n, x + 1, y, sum, steps, dp) : -DBL_MAX;
    if (right == -DBL_MAX && down == -DBL_MAX && (x == n - 1 && y == n - 1)) {
        dp[x][y] = sum / steps;
    } else if (right == -DBL_MAX || down == -DBL_MAX) {
        dp[x][y] = max(right, down);
    } else {
        double avgRight = (sum * (steps + 1) + right * steps) / (2 * steps + 1);
        double avgDown = (sum * (steps + 1) + down * steps) / (2 * steps + 1);
        dp[x][y] = max(avgRight, avgDown);
    }
    return dp[x][y];
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5.2, got 2.8933334350585938
  *  test case 1 failed: expected 6.2, got 4.2457141876220703
  *  test case 2 failed: expected 7.2, got 5.5980954170227051
  */

double maxAveragePath(int** matrix, int n) {
    double** dp = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        dp[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1.0;
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