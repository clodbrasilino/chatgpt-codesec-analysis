#include <stdio.h>
#include <stdlib.h>

int **generate_spiral_matrix(int n) {
    if (n <= 0) {
        return NULL;
    }

    int **matrix = malloc(n * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
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
    int num = 1;
    int max_num = n * n;

    while (num <= max_num) {
        for (int i = left; i <= right && num <= max_num; i++) {
            matrix[top][i] = num++;
        }
        top++;

        for (int i = top; i <= bottom && num <= max_num; i++) {
            matrix[i][right] = num++;
        }
        right--;

        for (int i = right; i >= left && num <= max_num; i--) {
            matrix[bottom][i] = num++;
        }
        bottom--;

        for (int i = bottom; i >= top && num <= max_num; i--) {
            matrix[i][left] = num++;
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
    int n = 4;
    int **matrix = generate_spiral_matrix(n);

    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix, n);

    return EXIT_SUCCESS;
}