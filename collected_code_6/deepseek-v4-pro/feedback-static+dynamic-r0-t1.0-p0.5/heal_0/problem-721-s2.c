#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void findMaxAveragePath(int **matrix, int n, int *path, int *pathLength, double *maxAverage) {
    int totalCells = n * n;
    int *dp = (int *)malloc(totalCells * sizeof(int));
    int *parent = (int *)malloc(totalCells * sizeof(int));
    double *avg = (double *)malloc(totalCells * sizeof(double));
    int *tempPath = (int *)malloc(totalCells * sizeof(int));
    
    if (!dp || !parent || !avg || !tempPath) {
        free(dp);
        free(parent);
        free(avg);
        free(tempPath);
        *pathLength = 0;
        *maxAverage = 0.0;
        return;
    }
    
    for (int i = 0; i < totalCells; i++) {
        dp[i] = matrix[i / n][i % n];
        parent[i] = -1;
        avg[i] = (double)dp[i];
    }
    
    for (int i = 0; i < totalCells; i++) {
        int row = i / n;
        int col = i % n;
        
        if (row > 0) {
            int up = i - n;
            double newAvg = (avg[up] * (dp[up] != 0 ? 1 : 0) + matrix[row][col]) / 2.0;
            if (dp[up] + matrix[row][col] > dp[i] || 
                (dp[up] + matrix[row][col] == dp[i] && newAvg > avg[i])) {
                dp[i] = dp[up] + matrix[row][col];
                parent[i] = up;
                avg[i] = newAvg;
            }
        }
        
        if (col > 0) {
            int left = i - 1;
            double newAvg = (avg[left] * (dp[left] != 0 ? 1 : 0) + matrix[row][col]) / 2.0;
            if (dp[left] + matrix[row][col] > dp[i] || 
                (dp[left] + matrix[row][col] == dp[i] && newAvg > avg[i])) {
                dp[i] = dp[left] + matrix[row][col];
                parent[i] = left;
                avg[i] = newAvg;
            }
        }
    }
    
    int endIndex = totalCells - 1;
    *maxAverage = avg[endIndex];
    
    int idx = endIndex;
    int count = 0;
    while (idx != -1) {
        tempPath[count++] = idx;
        idx = parent[idx];
    }
    
    *pathLength = count;
    for (int i = 0; i < count; i++) {
        path[i] = tempPath[count - 1 - i];
    }
    
    free(dp);
    free(parent);
    free(avg);
    free(tempPath);
}

int main() {
    int n = 3;
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    
    int testData[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = testData[i][j];
        }
    }
    
    int *path = (int *)malloc(n * n * sizeof(int));
    int pathLength = 0;
    double maxAverage = 0.0;
    
    findMaxAveragePath(matrix, n, path, &pathLength, &maxAverage);
    
    printf("Maximum average: %.2f\n", maxAverage);
    printf("Path: ");
    for (int i = 0; i < pathLength; i++) {
        printf("(%d,%d)", path[i] / n, path[i] % n);
        if (i < pathLength - 1) printf(" -> ");
    }
    printf("\n");
    
    free(path);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}