#include <stdio.h>
#include <stdlib.h>

void generate_magic_square(int n, int magic_square[n][n]) {
    int i, j, num = 1, row = 0, col = n / 2;

    for (i = 0; i < n * n; i++) {
        magic_square[row][col] = num++;
        row--;
        col++;

        if (num % n == 0) {
            row += 2;
            col--;
        } else {
            if (row < 0)
                row = n - 1;
            if (col == n)
                col = 0;
        }

        if (magic_square[row][col] != 0) {
            row += 2;
            col--;
            if (row >= n)
                row -= n;
            if (col < 0)
                col += n;
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the magic square (odd number): ");
    scanf("%d", &n);

    if (n % 2 == 0 || n < 1) {
        printf("Size must be an odd positive integer.\n");
        return 1;
    }

    int (*magic_square)[n] = malloc(n * sizeof(*magic_square));
    if (magic_square == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        magic_square[i] = malloc(n * sizeof(int));
        if (magic_square[i] == NULL) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(magic_square[j]);
            }
            free(magic_square);
            return 1;
        }
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