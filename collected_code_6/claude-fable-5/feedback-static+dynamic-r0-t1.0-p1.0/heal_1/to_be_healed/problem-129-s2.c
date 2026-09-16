#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int **allocate_square(size_t n);
static void free_square(int **square, size_t n);
static int generate_magic_square(int **square, size_t n);
static void print_square(int **square, size_t n);

static int **allocate_square(size_t n)
{
    int **square;
    size_t i;

    if (n == 0 || n > (size_t)(SIZE_MAX / sizeof(int *))) {
        return NULL;
    }

    square = calloc(n, sizeof(int *));
    if (square == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        square[i] = calloc(n, sizeof(int));
        if (square[i] == NULL) {
            free_square(square, i);
            return NULL;
        }
    }

    return square;
}

static void free_square(int **square, size_t n)
{
    size_t i;

    if (square == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

static int generate_magic_square(int **square, size_t n)
{
    size_t row;
    size_t col;
    size_t value;
    size_t total;
    /* Possible weaknesses found:
     *  The scope of the variable 'next_row' can be reduced. [variableScope]
     */
    size_t next_row;
    /* Possible weaknesses found:
     *  The scope of the variable 'next_col' can be reduced. [variableScope]
     */
    size_t next_col;

    if (square == NULL || n == 0 || (n % 2) == 0) {
        return -1;
    }

    if (n > (size_t)((size_t)INT_MAX / n)) {
        return -1;
    }

    total = n * n;
    row = 0;
    col = n / 2;

    for (value = 1; value <= total; value++) {
        square[row][col] = (int)value;

        next_row = (row == 0) ? (n - 1) : (row - 1);
        next_col = (col + 1) % n;

        if (square[next_row][next_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return 0;
}

static void print_square(int **square, size_t n)
{
    size_t i;
    size_t j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (printf("%6d", square[i][j]) < 0) {
                return;
            }
        }
        if (printf("\n") < 0) {
            return;
        }
    }
}

int main(void)
{
    int input;
    size_t n;
    int **square;

    if (printf("Enter the size of the magic square (odd number, 1-99): ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &input) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (input < 1 || input > 99 || (input % 2) == 0) {
        fprintf(stderr, "Error: size must be an odd number between 1 and 99.\n");
        return EXIT_FAILURE;
    }

    n = (size_t)input;

    square = allocate_square(n);
    if (square == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (generate_magic_square(square, n) != 0) {
        fprintf(stderr, "Error: failed to generate magic square.\n");
        free_square(square, n);
        return EXIT_FAILURE;
    }

    print_square(square, n);

    if (printf("Magic constant: %d\n", (int)(n * (n * n + 1) / 2)) < 0) {
        free_square(square, n);
        return EXIT_FAILURE;
    }

    free_square(square, n);
    return EXIT_SUCCESS;
}