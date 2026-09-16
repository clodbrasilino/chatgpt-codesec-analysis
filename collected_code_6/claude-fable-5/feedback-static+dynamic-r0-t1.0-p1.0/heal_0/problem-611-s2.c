#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 3

int find_max_of_nth_column(const int tuples[][COLS], size_t rows, size_t n, int *result)
{
    size_t i;
    int max;

    if (tuples == NULL || result == NULL) {
        return -1;
    }

    if (rows == 0U || n >= COLS) {
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
        {8, 9, 19},
        {2, 4, 6}
    };
    size_t n = 2U;
    int max_value = 0;
    int status;

    status = find_max_of_nth_column(tuples, (size_t)ROWS, n, &max_value);

    if (status != 0) {
        (void)fprintf(stderr, "Error: invalid input parameters.\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum of column %zu is %d\n", n, max_value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}