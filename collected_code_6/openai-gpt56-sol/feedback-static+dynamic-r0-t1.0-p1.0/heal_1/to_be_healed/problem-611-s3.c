#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int max_in_column(const int *tuples, size_t row_count, size_t column_count,
                         size_t column_index, int *maximum)
{
    size_t row;
    int current_max;

    if (tuples == NULL || maximum == NULL || row_count == 0 ||
        column_count == 0 || column_index >= column_count ||
        row_count > SIZE_MAX / column_count) {
        return -1;
    }

    current_max = tuples[column_index];

    for (row = 1; row < row_count; ++row) {
        int value = tuples[row * column_count + column_index];

        if (value > current_max) {
            current_max = value;
        }
    }

    *maximum = current_max;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     *  Variable 'tuples' can be declared as const array [constVariable]
     */
    int tuples[] = {
        3, 8, 2,
        5, 1, 9,
        4, 7, 6
    };
    const size_t row_count = 3;
    const size_t column_count = 3;
    const size_t column_index = 1;
    int maximum;

    errno = 0;

    if (max_in_column(tuples, row_count, column_count, column_index,
                      &maximum) != 0) {
        if (fputs("Unable to find the column maximum.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%d\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}