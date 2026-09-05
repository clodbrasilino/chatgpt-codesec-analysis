#include <stdio.h>
#include <stdlib.h>

int** generate_spiral_matrix(int n) {
    if (n <= 0) {
        return NULL;
    }

    int** matrix = (int**)malloc(n * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int value = 1;
    int limit = n * n;

    while (value <= limit) {
        for (int i = left; i <= right && value <= limit; i++) {
            matrix[top][i] = value * value;
            value++;
        }
        top++;

        for (int i = top; i <= bottom && value <= limit; i++) {
            matrix[i][right] = value * value;
            value++;
        }
        right--;

        for (int i = right; i >= left && value <= limit; i--) {
            matrix[bottom][i] = value * value;
            value++;
        }
        bottom--;

        for (int i = bottom; i >= top && value <= limit; i--) {
            matrix[i][left] = value * value;
            value++;
        }
        left++;
    }

    return matrix;
}

void free_matrix(int** matrix, int n) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n = 3;
    int** matrix = generate_spiral_matrix(n);

    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix, n);

    return EXIT_SUCCESS;
}