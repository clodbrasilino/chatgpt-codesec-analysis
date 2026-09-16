#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int maximum_in_column(const int *tuples, size_t row_count,
                             size_t column_count, size_t column,
                             int *maximum)
{
    if (tuples == NULL || maximum == NULL || row_count == 0U ||
        column_count == 0U || column >= column_count ||
        row_count > SIZE_MAX / column_count) {
        return -1;
    }

    int result = tuples[column];

    for (size_t row = 1U; row < row_count; ++row) {
        int value = tuples[row * column_count + column];
        if (value > result) {
            result = value;
        }
    }

    *maximum = result;
    return 0;
}

int main(void)
{
    size_t row_count;
    size_t column_count;
    size_t column;

    if (scanf("%zu %zu %zu", &row_count, &column_count, &column) != 3) {
        fprintf(stderr, "Invalid dimensions or column index.\n");
        return EXIT_FAILURE;
    }

    if (row_count == 0U || column_count == 0U || column >= column_count ||
        row_count > SIZE_MAX / column_count ||
        row_count * column_count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid input range.\n");
        return EXIT_FAILURE;
    }

    size_t element_count = row_count * column_count;
    int *tuples = malloc(element_count * sizeof(*tuples));

    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed: errno=%d\n", errno);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < element_count; ++i) {
        if (scanf("%d", &tuples[i]) != 1) {
            fprintf(stderr, "Invalid tuple value.\n");
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int maximum;
    if (maximum_in_column(tuples, row_count, column_count, column,
                          &maximum) != 0) {
        fprintf(stderr, "Unable to determine the maximum.\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%d\n", maximum);
    free(tuples);
    return EXIT_SUCCESS;
}