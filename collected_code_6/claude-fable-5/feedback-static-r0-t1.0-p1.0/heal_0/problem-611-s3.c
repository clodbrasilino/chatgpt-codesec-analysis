#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ROWS 3
#define COLS 3

int max_of_nth(const int tuples[][COLS], size_t rows, size_t n, int *result)
{
    size_t i;
    int max;

    if (tuples == NULL || result == NULL || rows == 0U || n >= COLS) {
        return -1;
    }

    max = tuples[0][n];
    for (i = 1U; i < rows; i++) {
        if (tuples[i][n] > max) {
            max = tuples[i][n];
        }
    }

    *result = max;
    return 0;
}

int main(void)
{
    const int tuples[ROWS][COLS] = {
        {5, 6, 7},
        {1, 3, 5},
        {8, 9, 19}
    };
    int result = INT_MIN;
    size_t n = 2U;

    if (max_of_nth(tuples, ROWS, n, &result) != 0) {
        if (fprintf(stderr, "Error: invalid input parameters\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum of column %zu: %d\n", n, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}