#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int **generate_magic_square(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }

    int **square = (int **)malloc(n * sizeof(int *));
    if (square == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        square[i] = (int *)calloc(n, sizeof(int));
        if (square[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
    }

    int row = 0;
    int col = n / 2;

    for (int num = 1; num <= n * n; num++) {
        square[row][col] = num;

        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;

        if (square[next_row][next_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return square;
}

void free_magic_square(int **square, int n) {
    if (square == NULL) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

void print_magic_square(int **square, int n) {
    if (square == NULL) {
        fprintf(stderr, "Invalid magic square.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", square[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, const char *argv[]) {
    int n = 3;

    if (argc > 1) {
        long val;
        char *endptr;
        errno = 0;
        val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX) {
            fprintf(stderr, "Error: n must be a positive odd integer.\n");
            return EXIT_FAILURE;
        }
        n = (int)val;
    }

    if (n <= 0 || n % 2 == 0) {
        fprintf(stderr, "Error: n must be a positive odd integer.\n");
        return EXIT_FAILURE;
    }

    int **square = generate_magic_square(n);
    if (square == NULL) {
        fprintf(stderr, "Error: failed to generate magic square.\n");
        return EXIT_FAILURE;
    }

    print_magic_square(square, n);

    int magic_sum = n * (n * n + 1) / 2;
    printf("\nMagic sum: %d\n", magic_sum);

    free_magic_square(square, n);

    return EXIT_SUCCESS;
}