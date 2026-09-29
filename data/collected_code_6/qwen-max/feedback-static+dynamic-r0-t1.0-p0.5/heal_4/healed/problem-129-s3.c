#include <stdio.h>
#include <stdlib.h>

void generate_magic_square(int n, int magic_square[n][n]) {
    int num = 1;
    int row = 0, col = n / 2;

    for (int i = 0; i < n * n; i++) {
        magic_square[row][col] = num++;
        row--;
        col++;

        if (num % n == 0) {
            row += 2;
            col--;
        } else if (row < 0) {
            row = n - 1;
        } else if (col == n) {
            col = 0;
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the magic square (odd number): ");
    scanf("%d", &n);

    if (n <= 0 || n % 2 == 0) {
        fprintf(stderr, "Size must be a positive odd number.\n");
        return 1;
    }

    int **magic_square = malloc(n * sizeof *magic_square);
    for (int i = 0; i < n; i++) {
        magic_square[i] = malloc(n * sizeof **magic_square);
    }

    generate_magic_square(n, magic_square);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", magic_square[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(magic_square[i]);
    }
    free(magic_square);

    return 0;
}