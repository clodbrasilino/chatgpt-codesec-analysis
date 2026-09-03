#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int **generate_spiral(int n) {
    if (n <= 0 || (long)n * n > INT_MAX) {
        return NULL;
    }

    int **matrix = malloc((size_t)n * sizeof(*matrix));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = malloc((size_t)n * sizeof(*matrix[i]));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    int value = 1;
    int total = n * n;

    while (value <= total) {
        for (int col = left; col <= right && value <= total; col++) {
            matrix[top][col] = value++;
        }
        top++;

        for (int row = top; row <= bottom && value <= total; row++) {
            matrix[row][right] = value++;
        }
        right--;

        for (int col = right; col >= left && value <= total; col--) {
            matrix[bottom][col] = value++;
        }
        bottom--;

        for (int row = bottom; row >= top && value <= total; row--) {
            matrix[row][left] = value++;
        }
        left++;
    }

    return matrix;
}

void free_matrix(int **matrix, int n) {
    if (matrix == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void) {
    int n = 5;
    int **matrix = generate_spiral(n);

    if (matrix == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix, n);
    return 0;
}