#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int** generate_magic_square(int n);
void print_matrix(int** matrix, int n);
void free_matrix(int** matrix, int n);

int** generate_magic_square(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }

    int** matrix = (int**)malloc((size_t)n * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc((size_t)n, sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    int r = n / 2;
    int c = n - 1;

    for (int num = 1; num <= n * n; num++) {
        matrix[r][c] = num;
        
        int next_r = r - 1;
        int next_c = c + 1;

        if (next_r == -1 && next_c == n) {
            next_r = 0;
            next_c = n - 2;
        } else {
            if (next_c == n) {
                next_c = 0;
            }
            if (next_r < 0) {
                next_r = n - 1;
            }
        }

        if (matrix[next_r][next_c] != 0) {
            next_r = r;
            next_c = c - 1;
        }

        r = next_r;
        c = next_c;
    }

    return matrix;
}

void print_matrix(int** matrix, int n) {
    if (matrix == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(int** matrix, int n) {
    if (matrix == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <odd_positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val <= 0 || val > INT_MAX || val % 2 == 0) {
        fprintf(stderr, "Invalid input. Please provide a positive odd integer.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    int** magic_square = generate_magic_square(n);

    if (magic_square == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid dimension.\n");
        return EXIT_FAILURE;
    }

    print_matrix(magic_square, n);
    free_matrix(magic_square, n);

    return EXIT_SUCCESS;
}