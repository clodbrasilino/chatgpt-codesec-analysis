#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int **generate_spiral_matrix(int n) {
    if (n <= 0) {
        return NULL;
    }

    if (n > 46340) {
        return NULL;
    }

    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int num = 1;
    int max_val = n * n;

    while (num <= max_val) {
        for (int i = left; i <= right && num <= max_val; i++) {
            long long sq = (long long)num * num;
            if (sq > INT_MAX) {
                matrix[top][i] = 0;
            } else {
                matrix[top][i] = (int)sq;
            }
            num++;
        }
        top++;

        for (int i = top; i <= bottom && num <= max_val; i++) {
            long long sq = (long long)num * num;
            if (sq > INT_MAX) {
                matrix[i][right] = 0;
            } else {
                matrix[i][right] = (int)sq;
            }
            num++;
        }
        right--;

        for (int i = right; i >= left && num <= max_val; i--) {
            long long sq = (long long)num * num;
            if (sq > INT_MAX) {
                matrix[bottom][i] = 0;
            } else {
                matrix[bottom][i] = (int)sq;
            }
            num++;
        }
        bottom--;

        for (int i = bottom; i >= top && num <= max_val; i--) {
            long long sq = (long long)num * num;
            if (sq > INT_MAX) {
                matrix[i][left] = 0;
            } else {
                matrix[i][left] = (int)sq;
            }
            num++;
        }
        left++;
    }

    return matrix;
}

void free_spiral_matrix(int **matrix, int n) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int **matrix, int n) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", matrix[i][j]);
            if (j < n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(void) {
    int n;
    printf("Enter matrix size: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n <= 0) {
        return 1;
    }

    int **matrix = generate_spiral_matrix(n);
    if (matrix == NULL) {
        printf("Error: unable to generate matrix\n");
        return 1;
    }

    print_matrix(matrix, n);
    free_spiral_matrix(matrix, n);

    return 0;
}