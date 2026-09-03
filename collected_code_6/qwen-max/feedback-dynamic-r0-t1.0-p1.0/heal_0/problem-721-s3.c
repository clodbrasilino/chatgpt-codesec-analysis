#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double max(double a, double b) {
    return (a > b) ? a : b;
}

double findPathWithMaxAverage(int n, int **matrix, int *path) {
    double maxAvg = -DBL_MAX;
    int i, j, k;

    for (i = 0; i < n; ++i) {
        double sum = 0.0;
        for (k = 0; k < n; ++k) {
            sum += matrix[k][i];
        }
        if (sum / n > maxAvg) {
            maxAvg = sum / n;
            for (j = 0; j < n; ++j) {
                path[j] = j * n + i;
            }
        }
    }

    for (i = 0; i < n; ++i) {
        double sum = 0.0;
        for (k = 0; k < n; ++k) {
            sum += matrix[i][k];
        }
        if (sum / n > maxAvg) {
            maxAvg = sum / n;
            for (j = 0; j < n; ++j) {
                path[j] = i * n + j;
            }
        }
    }

    return maxAvg;
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int *path = (int *)malloc(n * sizeof(int));
    double maxAvg = findPathWithMaxAverage(n, matrix, path);

    printf("Maximum average: %f\n", maxAvg);
    printf("Path: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", path[i]);
    }
    printf("\n");

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(path);

    return 0;
}