#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_column(int **lists, const size_t *row_lengths, size_t num_rows, size_t col_index, long *result)
{
    size_t i;
    long sum;

    if (lists == NULL || row_lengths == NULL || result == NULL) {
        return -1;
    }
    if (num_rows == 0) {
        return -1;
    }

    sum = 0;
    for (i = 0; i < num_rows; i++) {
        int value;

        if (lists[i] == NULL) {
            return -1;
        }
        if (col_index >= row_lengths[i]) {
            return -1;
        }

        value = lists[i][col_index];
        if ((value > 0 && sum > LONG_MAX - value) ||
            (value < 0 && sum < LONG_MIN - value)) {
            return -1;
        }
        sum += value;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const size_t num_rows = 3;
    const size_t col_index = 1;
    int **lists = NULL;
    size_t *row_lengths = NULL;
    long result = 0;
    size_t i;
    size_t j;
    int status = EXIT_SUCCESS;

    lists = malloc(num_rows * sizeof(*lists));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    row_lengths = malloc(num_rows * sizeof(*row_lengths));
    if (row_lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(lists);
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_rows; i++) {
        lists[i] = NULL;
        row_lengths[i] = i + 2;
    }

    for (i = 0; i < num_rows; i++) {
        lists[i] = malloc(row_lengths[i] * sizeof(**lists));
        if (lists[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(lists[j]);
            }
            free(lists);
            free(row_lengths);
            return EXIT_FAILURE;
        }
        for (j = 0; j < row_lengths[i]; j++) {
            lists[i][j] = (int)(i * 10 + j + 1);
        }
    }

    if (sum_column(lists, row_lengths, num_rows, col_index, &result) != 0) {
        fprintf(stderr, "Failed to sum column %zu\n", col_index);
        status = EXIT_FAILURE;
    } else {
        printf("Sum of column %zu: %ld\n", col_index, result);
    }

    for (i = 0; i < num_rows; i++) {
        free(lists[i]);
    }
    free(lists);
    free(row_lengths);

    return status;
}