#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <sys/types.h>

#define MAX_ORDER 46339

int **allocate_square(int n)
{
    int **square;
    int i;

    if (n <= 0) {
        return NULL;
    }
    if ((size_t)n > SIZE_MAX / sizeof(*square)) {
        return NULL;
    }
    if ((size_t)n > SIZE_MAX / sizeof(**square)) {
        return NULL;
    }
    square = malloc((size_t)n * sizeof(*square));
    if (square == NULL) {
        return NULL;
    }
    for (i = 0; i < n; i++) {
        square[i] = calloc((size_t)n, sizeof(*square[i]));
        if (square[i] == NULL) {
            while (i > 0) {
                i--;
                free(square[i]);
            }
            free(square);
            return NULL;
        }
    }
    return square;
}

void free_square(int **square, int n)
{
    int i;

    if (square == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

int generate_magic_square(int **square, int n)
{
    int row;
    int col;
    long num;
    long total;

    if (square == NULL || n <= 0 || n % 2 == 0) {
        return -1;
    }
    total = (long)n * (long)n;
    row = 0;
    col = n / 2;
    for (num = 1; num <= total; num++) {
        int new_row;
        int new_col;

        square[row][col] = (int)num;
        new_row = (row - 1 + n) % n;
        new_col = (col + 1) % n;
        if (square[new_row][new_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = new_row;
            col = new_col;
        }
    }
    return 0;
}

void print_square(int **square, int n)
{
    int i;
    int j;

    if (square == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        if (square[i] == NULL) {
            return;
        }
        for (j = 0; j < n; j++) {
            printf("%4d", square[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    char *buffer;
    size_t buffer_size;
    ssize_t line_length;
    char *end;
    long value;
    int n;
    int **square;
    long magic_constant;

    buffer = NULL;
    buffer_size = 0;

    printf("Enter a positive odd integer for the magic square order: ");
    fflush(stdout);

    line_length = getline(&buffer, &buffer_size, stdin);
    if (line_length < 0) {
        fprintf(stderr, "Invalid input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    errno = 0;
    value = strtol(buffer, &end, 10);
    if (errno != 0 || end == buffer) {
        fprintf(stderr, "Invalid input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        end++;
    }
    if (*end != '\0') {
        fprintf(stderr, "Invalid input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    if (value <= 0 || value > MAX_ORDER || value % 2 == 0) {
        fprintf(stderr, "Order must be a positive odd integer no larger than %d.\n", MAX_ORDER);
        free(buffer);
        return EXIT_FAILURE;
    }
    n = (int)value;
    free(buffer);
    buffer = NULL;

    square = allocate_square(n);
    if (square == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    if (generate_magic_square(square, n) != 0) {
        fprintf(stderr, "Failed to generate magic square.\n");
        free_square(square, n);
        return EXIT_FAILURE;
    }
    print_square(square, n);
    magic_constant = (long)n * ((long)n * (long)n + 1L) / 2L;
    printf("Magic constant: %ld\n", magic_constant);
    free_square(square, n);
    return EXIT_SUCCESS;
}