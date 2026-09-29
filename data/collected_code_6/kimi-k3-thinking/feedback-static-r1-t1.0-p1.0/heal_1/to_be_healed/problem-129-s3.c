#include <stdio.h>
#include <stdlib.h>

int **allocate_square(int n)
{
    int **square;
    int i;

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
    int num;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_row' can be reduced. [variableScope]
     */
    int new_row;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_col' can be reduced. [variableScope]
     */
    int new_col;

    if (square == NULL || n <= 0 || n % 2 == 0) {
        return -1;
    }
    row = 0;
    col = n / 2;
    for (num = 1; num <= n * n; num++) {
        square[row][col] = num;
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

void print_square(const int **square, int n)
{
    int i;
    int j;

    if (square == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d", square[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int n;
    int **square;
    long magic_constant;

    printf("Enter a positive odd integer for the magic square order: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    if (n <= 0 || n % 2 == 0) {
        fprintf(stderr, "Order must be a positive odd integer.\n");
        return EXIT_FAILURE;
    }
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
    print_square((const int **)square, n);
    magic_constant = (long)n * ((long)n * n + 1L) / 2L;
    printf("Magic constant: %ld\n", magic_constant);
    free_square(square, n);
    return EXIT_SUCCESS;
}