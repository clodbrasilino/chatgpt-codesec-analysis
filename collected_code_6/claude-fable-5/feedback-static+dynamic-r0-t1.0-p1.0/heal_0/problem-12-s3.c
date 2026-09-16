#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 3

static long row_sum(const int *row, size_t cols)
{
    long sum = 0;
    size_t j;

    for (j = 0; j < cols; j++) {
        sum += row[j];
    }
    return sum;
}

static void swap_rows(int *a, int *b, size_t cols)
{
    size_t j;
    int tmp;

    for (j = 0; j < cols; j++) {
        tmp = a[j];
        a[j] = b[j];
        b[j] = tmp;
    }
}

static int sort_matrix_by_row_sum(int matrix[][COLS], size_t rows, size_t cols)
{
    size_t i;
    size_t k;

    if (matrix == NULL || rows == 0 || cols == 0) {
        return -1;
    }

    for (i = 0; i + 1 < rows; i++) {
        for (k = 0; k + 1 < rows - i; k++) {
            long sum_a = row_sum(matrix[k], cols);
            long sum_b = row_sum(matrix[k + 1], cols);

            if (sum_a > sum_b) {
                swap_rows(matrix[k], matrix[k + 1], cols);
            }
        }
    }
    return 0;
}

static void print_matrix(const int matrix[][COLS], size_t rows, size_t cols)
{
    size_t i;
    size_t j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (printf("%d ", matrix[i][j]) < 0) {
                exit(EXIT_FAILURE);
            }
        }
        if (printf("\n") < 0) {
            exit(EXIT_FAILURE);
        }
    }
}

int main(void)
{
    int matrix[ROWS][COLS] = {
        {9, 8, 7},
        {1, 2, 3},
        {4, 6, 5},
        {0, 1, 1}
    };

    if (printf("Original matrix:\n") < 0) {
        return EXIT_FAILURE;
    }
    print_matrix(matrix, ROWS, COLS);

    if (sort_matrix_by_row_sum(matrix, ROWS, COLS) != 0) {
        if (fprintf(stderr, "Error: invalid matrix input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Sorted matrix by row sum:\n") < 0) {
        return EXIT_FAILURE;
    }
    print_matrix(matrix, ROWS, COLS);

    return EXIT_SUCCESS;
}