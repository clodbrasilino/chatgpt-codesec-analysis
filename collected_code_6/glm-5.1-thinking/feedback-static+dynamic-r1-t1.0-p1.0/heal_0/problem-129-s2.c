#include <stdio.h>
#include <stdlib.h>

int* generateMagicSquare(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }

    int* magic = (int*)malloc(n * n * sizeof(int));
    if (magic == NULL) {
        return NULL;
    }

    for (int i = 0; i < n * n; i++) {
        magic[i] = 0;
    }

    int row = 0;
    int col = n / 2;

    for (int num = 1; num <= n * n; num++) {
        magic[row * n + col] = num;

        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;

        if (magic[next_row * n + next_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return magic;
}

int main(void) {
    int n = 5;
    int* square = generateMagicSquare(n);

    if (square == NULL) {
        fprintf(stderr, "Failed to generate magic square.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", square[i * n + j]);
        }
        printf("\n");
    }

    free(square);
    square = NULL;

    return EXIT_SUCCESS;
}