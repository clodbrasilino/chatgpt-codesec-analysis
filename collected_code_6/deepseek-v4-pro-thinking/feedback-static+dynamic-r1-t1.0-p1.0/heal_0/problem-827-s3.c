#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool sum_column(const int * const *matrix, size_t rows, size_t cols, size_t column, int *result) {
    if (matrix == NULL || result == NULL || rows == 0 || cols == 0 || column >= cols) {
        return false;
    }

    int sum = 0;
    for (size_t r = 0; r < rows; ++r) {
        if (matrix[r] == NULL) {
            return false;
        }
        sum += matrix[r][column];
    }

    *result = sum;
    return true;
}

int main(void) {
    int row0[] = { 1, 2, 3 };
    int row1[] = { 4, 5, 6 };
    int row2[] = { 7, 8, 9 };
    const int * const matrix[] = { row0, row1, row2 };
    int result = 0;

    if (sum_column(matrix, 3, 3, 1, &result)) {
        printf("%d\n", result);
    } else {
        printf("Error\n");
    }

    return 0;
}