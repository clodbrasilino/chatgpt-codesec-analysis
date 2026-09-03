#include <stdio.h>
#include <stdlib.h>

int **generate_spiral(int n)
{
    if (n <= 0) {
        return NULL;
    }

    int **matrix = malloc((size_t)n * sizeof(*matrix));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = malloc((size_t)n * sizeof(*matrix[i]));
        if (matrix[i] == NULL) {
            while (i > 0) {
                free(matrix[--i]);
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

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            matrix[top][i] = value++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = value++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = value++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = value++;
            }
            left++;
        }
    }

    return matrix;
}

int main(void)
{
    int n = 5;
    int **matrix = generate_spiral(n);

    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}