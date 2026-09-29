#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

int **generate_magic_square(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }

    if (n > INT_MAX / n) {
        return NULL;
    }

    int **square = (int **)malloc((size_t)n * sizeof(int *));
    if (square == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        square[i] = (int *)calloc((size_t)n, sizeof(int));
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
    if (square == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(square[i]);
        square[i] = NULL;
    }
    free(square);
}

void print_magic_square(int **square, int n) {
    if (square == NULL || n <= 0) {
        printf("Invalid magic square\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (square[i] == NULL) {
            printf("Invalid magic square\n");
            return;
        }
        for (int j = 0; j < n; j++) {
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int n = 0;
    char buffer[256];
    size_t buffer_size = sizeof(buffer);

    printf("Enter odd number for magic square size: ");
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }

    size_t len = strlen(buffer);
    if (len == 0 || buffer[len - 1] != '\n') {
        if (len == buffer_size - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
        printf("Input too long\n");
        return 1;
    }

    buffer[len - 1] = '\0';
    len--;

    if (len == 0) {
        printf("Invalid input\n");
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        if (i == 0 && buffer[i] == '-') {
            continue;
        }
        if (buffer[i] < '0' || buffer[i] > '9') {
            printf("Invalid input\n");
            return 1;
        }
    }

    char *endptr = NULL;
    errno = 0;
    long val = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0') {
        printf("Invalid input\n");
        return 1;
    }

    if (val <= 0 || val > INT_MAX) {
        printf("Invalid input\n");
        return 1;
    }

    n = (int)val;

    if (n % 2 == 0) {
        printf("Please enter a positive odd number\n");
        return 1;
    }

    if (n > INT_MAX / n) {
        printf("Size too large\n");
        return 1;
    }

    int **magic_square = generate_magic_square(n);
    if (magic_square == NULL) {
        printf("Failed to generate magic square\n");
        return 1;
    }

    print_magic_square(magic_square, n);
    free_magic_square(magic_square, n);

    return 0;
}