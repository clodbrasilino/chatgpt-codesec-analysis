#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* Possible weaknesses found:
 *  expected 'const int * const*' but argument is of type 'int **'
 */
int extract_elements(const int * const *grid, size_t rows, size_t cols,
                     const size_t (*indices)[2], size_t count, int *out)
{
    size_t i;

    if (grid == NULL) {
        return -1;
    }
    if (rows == 0 || cols == 0) {
        return -1;
    }
    if (indices == NULL && count > 0) {
        return -1;
    }
    if (out == NULL && count > 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        size_t row = indices[i][0];
        size_t col = indices[i][1];

        if (row >= rows || col >= cols) {
            return -1;
        }
        if (grid[row] == NULL) {
            return -1;
        }
        out[i] = grid[row][col];
    }

    return 0;
}

int main(void)
{
    enum { ROWS = 2, COLS = 3 };

    int **grid;
    size_t i;
    int init_values[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    size_t indices[][2] = {
        {0, 1},
        {1, 2},
        {1, 0}
    };
    const size_t count = sizeof(indices) / sizeof(indices[0]);
    int *extracted;
    int result;

    grid = malloc(ROWS * sizeof(*grid));
    if (grid == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < ROWS; i++) {
        grid[i] = malloc(COLS * sizeof(*grid[i]));
        if (grid[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < ROWS; i++) {
        size_t j;
        for (j = 0; j < COLS; j++) {
            grid[i][j] = init_values[i][j];
        }
    }

    extracted = malloc(count * sizeof(*extracted));
    if (extracted == NULL) {
        for (i = 0; i < ROWS; i++) {
            free(grid[i]);
        }
        free(grid);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  passing argument 1 of 'extract_elements' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    result = extract_elements(grid, ROWS, COLS, indices, count, extracted);
    if (result != 0) {
        free(extracted);
        for (i = 0; i < ROWS; i++) {
            free(grid[i]);
        }
        free(grid);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%d\n", extracted[i]);
    }

    free(extracted);
    for (i = 0; i < ROWS; i++) {
        free(grid[i]);
    }
    free(grid);

    return EXIT_SUCCESS;
}