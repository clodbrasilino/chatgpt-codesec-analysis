#include <stdio.h>
#include <stdlib.h>

int **generate_spiral_matrix(int n) {
    if (n <= 0) {
        return NULL;
    }

    int **matrix = malloc((size_t)n * sizeof(*matrix));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc((size_t)n * sizeof(*matrix[i]));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    int value = 1;
    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;

    while (top <= bottom && left <= right) {
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[row][left] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

int main(void) {
    int n = 5;
    int **matrix = generate_spiral_matrix(n);

    if (matrix == NULL) {
        fprintf(stderr, "Failed to generate spiral matrix\n");
        return EXIT_FAILURE;
    }

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            printf("%3d ", matrix[row][col]);
        }
        printf("\n");
    }

    for (int row = 0; row < n; ++row) {
        free(matrix[row]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}