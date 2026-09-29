#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int **allocate_square(size_t n)
{
    int **square;
    size_t i;
    size_t j;

    square = malloc(n * sizeof(*square));
    if (square == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        square[i] = calloc(n, sizeof(**square));
        if (square[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
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
    /* Possible weaknesses found:
     *  The scope of the variable 'next_row' can be reduced. [variableScope]
     */
    size_t next_row;
    /* Possible weaknesses found:
     *  The scope of the variable 'next_col' can be reduced. [variableScope]
     */
    size_t next_col;
    size_t total;
    size_t value;

    if (square == NULL || n == 0U || (n % 2U) == 0U) {
        return -1;
    }

    if (n > (size_t)INT_MAX || n > ((size_t)INT_MAX / n)) {
        return -1;
    }

    total = n * n;
    row = 0;
    col = n / 2U;

    for (value = 1U; value <= total; value++) {
        square[row][col] = (int)value;

        next_row = (row == 0U) ? (n - 1U) : (row - 1U);
        next_col = (col == n - 1U) ? 0U : (col + 1U);

        if (square[next_row][next_col] != 0) {
            row = (row == n - 1U) ? 0U : (row + 1U);
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return 0;
}

static int print_square(int **square, size_t n)
{
    size_t i;
    size_t j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (printf("%6d", square[i][j]) < 0) {
                return -1;
            }
        }
        if (printf("\n") < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t n;
    unsigned long input;
    int **square;
    int result;

    if (printf("Enter an odd size for the magic square: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lu", &input) != 1) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input == 0UL || (input % 2UL) == 0UL || input > 99UL) {
        (void)fprintf(stderr, "Size must be an odd number between 1 and 99\n");
        return EXIT_FAILURE;
    }

    n = (size_t)input;

    square = allocate_square(n);
    if (square == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = generate_magic_square(square, n);
    if (result != 0) {
        (void)fprintf(stderr, "Failed to generate magic square\n");
        free_square(square, n);
        return EXIT_FAILURE;
    }

    if (print_square(square, n) != 0) {
        free_square(square, n);
        return EXIT_FAILURE;
    }

    if (printf("Magic constant: %lu\n",
               (unsigned long)(n * (n * n + 1U) / 2U)) < 0) {
        free_square(square, n);
        return EXIT_FAILURE;
    }

    free_square(square, n);
    return EXIT_SUCCESS;
}