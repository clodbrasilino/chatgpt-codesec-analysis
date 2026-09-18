#include <stdio.h>
#include <stdlib.h>

void free_magic_square(int **square, int allocated_rows) {
    if (!square) {
        return;
    }
    for (int i = 0; i < allocated_rows; i++) {
        free(square[i]);
    }
    free(square);
}

int **generate_magic_square(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }

    int **square = (int **)malloc((size_t)n * sizeof(int *));
    if (!square) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        square[i] = (int *)calloc((size_t)n, sizeof(int));
        if (!square[i]) {
            free_magic_square(square, i);
            return NULL;
        }
    }

    int row = 0;
    int col = n / 2;

    for (int num = 1; num <= n * n; num++) {
        square[row][col] = num;

        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;

        if (square[next_row][next_col]) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return square;
}

int main(void) {
    int n = 0;

    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n <= 0 || n % 2 == 0) {
        return EXIT_FAILURE;
    }

    int **magic_square = generate_magic_square(n);
    if (!magic_square) {
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