#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double max(double a, double b) {
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 7.2, got 8.3333330154418945
  *  test case 1 failed: expected 6.2, got 7.3333334922790527
  *  test case 0 failed: expected 5.2, got 6.3333334922790527
  */

double findMaxAveragePath(int **grid, int n) {
    double maxAvg = DBL_MIN;
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        int count = 0;
        for (int j = 0; j < n; j++) {
            sum += grid[i][j];
            count++;
        }
        if (count > 0) {
            maxAvg = max(maxAvg, sum / count);
        }
    }

    for (int j = 0; j < n; j++) {
        double sum = 0.0;
        int count = 0;
        for (int i = 0; i < n; i++) {
            sum += grid[i][j];
            count++;
        }
        if (count > 0) {
            maxAvg = max(maxAvg, sum / count);
        }
    }

    double diag1Sum = 0.0, diag2Sum = 0.0;
    for (int i = 0; i < n; i++) {
        diag1Sum += grid[i][i];
        diag2Sum += grid[i][n - 1 - i];
    }
    if (n > 0) {
        maxAvg = max(maxAvg, diag1Sum / n);
        maxAvg = max(maxAvg, diag2Sum / n);
    }

    return maxAvg;
}

int main() {
    int n;
    scanf("%d", &n);

    int **grid = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grid[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    double result = findMaxAveragePath(grid, n);
    printf("%.8f\n", result);

    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}