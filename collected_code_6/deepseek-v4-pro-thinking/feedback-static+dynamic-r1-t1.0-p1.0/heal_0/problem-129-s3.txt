#include <stdio.h>
#include <stdlib.h>

int **magic_square(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }
    int **square = malloc(n * sizeof(int *));
    if (square == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        square[i] = malloc(n * sizeof(int));
        if (square[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
        for (int j = 0; j < n; j++) {
            square[i][j] = 0;
        }
    }
    int row = 0;
    int col = n / 2;
    for (int num = 1; num <= n * n; num++) {
        square[row][col] = num;
        int new_row = (row - 1 + n) % n;
        int new_col = (col + 1) % n;
        if (square[new_row][new_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = new_row;
            col = new_col;
        }
    }
    return square;
}

int main(void) {
    int n;
    printf("Enter odd order for magic square: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    int **square = magic_square(n);
    if (square == NULL) {
        fprintf(stderr, "Failed to generate magic square. Only odd positive order is supported.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", square[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
    return EXIT_SUCCESS;
}