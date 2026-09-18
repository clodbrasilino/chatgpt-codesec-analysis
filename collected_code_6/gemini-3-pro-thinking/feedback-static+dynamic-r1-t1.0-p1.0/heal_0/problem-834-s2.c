#include <stdio.h>
#include <stdlib.h>

int** generate_spiral_matrix(int n);
void free_matrix(int **matrix, int n);
void print_matrix(int **matrix, int n);

int** generate_spiral_matrix(int n) {
    if (n <= 0) {
        return NULL;
    }

    int **matrix = (int **)malloc((size_t)n * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc((size_t)n * sizeof(int));
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

void free_matrix(int **matrix, int n) {
    if (matrix == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int **matrix, int n) {
    if (matrix == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int n = 5;
    
    int **spiral_matrix = generate_spiral_matrix(n);
    if (spiral_matrix == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid size.\n");
        return EXIT_FAILURE;
    }

    print_matrix(spiral_matrix, n);
    free_matrix(spiral_matrix, n);

    return EXIT_SUCCESS;
}