#include <stdio.h>
#include <stdlib.h>

int** create_magic_square(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }

    int** matrix = (int**)malloc(n * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    int row = n - 1;
    int col = n / 2;

    for (int num = 1; num <= n * n; num++) {
        matrix[row][col] = num;

        int next_row = (row + 1) % n;
        int next_col = (col + 1) % n;

        if (matrix[next_row][next_col] != 0) {
            row = (row - 1 + n) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return matrix;
}

void free_magic_square(int** matrix, int n) {
    if (matrix == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <odd_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if (n <= 0 || n % 2 == 0) {
        fprintf(stderr, "Error: Size must be a positive odd integer.\n");
        return EXIT_FAILURE;
    }

    int** magic_square = create_magic_square(n);
    if (magic_square == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", magic_square[i][j]);
        }
        printf("\n");
    }

    free_magic_square(magic_square, n);

    return EXIT_SUCCESS;
}