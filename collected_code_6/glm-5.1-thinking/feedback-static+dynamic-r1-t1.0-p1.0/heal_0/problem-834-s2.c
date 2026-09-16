#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int** generate_spiral_matrix(int n) {
    if (n <= 0) {
        return NULL;
    }

    int** matrix = (int**)malloc(n * sizeof(int*));
    if (!matrix) {
        return NULL;
    }

    int* values = (int*)malloc((size_t)n * n * sizeof(int));
    if (!values) {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = values + (size_t)i * n;
    }

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    int num = 1;
    int limit = n * n;

    while (num <= limit) {
        for (int i = left; i <= right && num <= limit; i++) {
            matrix[top][i] = num++;
        }
        top++;

        for (int i = top; i <= bottom && num <= limit; i++) {
            matrix[i][right] = num++;
        }
        right--;

        for (int i = right; i >= left && num <= limit; i--) {
            matrix[bottom][i] = num++;
        }
        bottom--;

        for (int i = bottom; i >= top && num <= limit; i--) {
            matrix[i][left] = num++;
        }
        left++;
    }

    return matrix;
}

void free_matrix(int** matrix) {
    if (matrix != NULL) {
        free(matrix[0]);
        free(matrix);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 46340) {
        fprintf(stderr, "Invalid size. Must be a positive integer up to 46340.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    int** matrix = generate_spiral_matrix(n);

    if (matrix == NULL) {
        fprintf(stderr, "Failed to allocate matrix.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix);

    return EXIT_SUCCESS;
}