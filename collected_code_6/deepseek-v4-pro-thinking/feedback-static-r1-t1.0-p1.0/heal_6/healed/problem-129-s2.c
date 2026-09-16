#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int **generate_magic_square(int n)
{
    if (n <= 0 || n % 2 == 0 || n > INT_MAX / n) {
        errno = EINVAL;
        return NULL;
    }

    int **square = malloc((size_t)n * sizeof(*square));
    if (square == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        square[i] = calloc((size_t)n, sizeof(*square[i]));
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

void free_magic_square(int **square, int n)
{
    if (square == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

int main(int argc, char **argv)
{
    int n = 5;

    if (argc > 1) {
        char *endptr;
        long value = strtol(argv[1], &endptr, 10);

        if (*endptr != '\0' || value <= 0 || value > INT_MAX || value % 2 == 0) {
            fprintf(stderr, "Usage: %s <positive odd integer>\n", argv[0]);
            return EXIT_FAILURE;
        }

        n = (int)value;
    }

    int **square = generate_magic_square(n);
    if (square == NULL) {
        perror("generate_magic_square");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", square[i][j]);
        }
        printf("\n");
    }

    free_magic_square(square, n);
    return EXIT_SUCCESS;
}