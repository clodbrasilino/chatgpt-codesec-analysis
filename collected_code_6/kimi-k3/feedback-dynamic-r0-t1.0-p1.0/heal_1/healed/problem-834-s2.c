#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

void generateSpiralMatrix(int n, int **matrix) {
    int num = 1;
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;

    while (num <= n * n) {
        for (int i = left; i <= right; i++) {
            matrix[top][i] = num++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = num++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = num++;
            }
            left++;
        }
    }
}

void printMatrix(int n, int **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int n, int **matrix) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void) {
    int n;

    printf("Enter the size of the matrix: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if ((size_t)n > SIZE_MAX / sizeof(int *) || (size_t)n > SIZE_MAX / sizeof(int) || (size_t)n * (size_t)n > INT_MAX) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }

    int **matrix = malloc((size_t)n * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = malloc((size_t)n * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    generateSpiralMatrix(n, matrix);
    printMatrix(n, matrix);
    freeMatrix(n, matrix);

    return EXIT_SUCCESS;
}