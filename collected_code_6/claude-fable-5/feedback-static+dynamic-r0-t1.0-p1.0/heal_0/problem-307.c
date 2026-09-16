#include <stdio.h>
#include <stdlib.h>

int *get_colon_of_tuple(const int *tuples, size_t rows, size_t cols, size_t col_index)
{
    int *result;
    size_t i;

    if (tuples == NULL || rows == 0 || cols == 0 || col_index >= cols) {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    result = malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        result[i] = tuples[i * cols + col_index];
    }

    return result;
}

int main(void)
{
    int tuples[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };
    size_t rows = 4;
    size_t cols = 3;
    size_t col_index = 1;
    int *column;
    size_t i;

    column = get_colon_of_tuple(&tuples[0][0], rows, cols, col_index);
    if (column == NULL) {
        fprintf(stderr, "Error: failed to extract column from tuple\n");
        return EXIT_FAILURE;
    }

    printf("Column %zu of the tuple:", col_index);
    for (i = 0; i < rows; i++) {
        printf(" %d", column[i]);
    }
    printf("\n");

    free(column);
    column = NULL;

    return EXIT_SUCCESS;
}