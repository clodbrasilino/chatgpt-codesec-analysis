#include <stdio.h>
#include <stdlib.h>

int** create_magic_square(int n, int* size) {
    if (n < 1 || n > 100) return NULL;
    *size = n;
    int** magic_square = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        magic_square[i] = (int*)calloc(n, sizeof(int));
    }
    int num = 1;
    int i = 0, j = n / 2;
    while (num <= n * n) {
        magic_square[i][j] = num++;
        i--;
        j++;
        if (i < 0) i = n - 1;
        if (j >= n) j = 0;
        if (magic_square[i][j] != 0) {
            i += 2;
            j -= 1;
            if (i >= n) i = 1;
            if (j < 0) j = 0;
        }
    }
    return magic_square;
}

void print_magic_square(int** magic_square, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d", magic_square[i][j]);
        }
        printf("\n");
    }
}

void free_magic_square(int** magic_square, int n) {
    for (int i = 0; i < n; ++i) {
        free(magic_square[i]);
    }
    free(magic_square);
}

int main() {
    int n = 3;
    int size;
    int** magic_square = create_magic_square(n, &size);
    if (magic_square != NULL) {
        print_magic_square(magic_square, size);
        free_magic_square(magic_square, size);
    } else {
        printf("Failed to create magic square.\n");
    }
    return 0;
}