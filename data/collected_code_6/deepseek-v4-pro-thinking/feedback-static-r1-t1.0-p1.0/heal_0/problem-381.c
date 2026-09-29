#include <stdio.h>
#include <stdlib.h>

static size_t sort_column;

int compare_rows(const void *a, const void *b) {
    const int *row_a = *(const int * const *)a;
    const int *row_b = *(const int * const *)b;

    if (row_a[sort_column] < row_b[sort_column]) {
        return -1;
    }
    if (row_a[sort_column] > row_b[sort_column]) {
        return 1;
    }
    return 0;
}

void sort_list_of_lists(int **list, size_t row_count, size_t col_count, size_t index) {
    if (list == NULL || row_count == 0 || col_count == 0 || index >= col_count) {
        return;
    }

    for (size_t i = 0; i < row_count; ++i) {
        if (list[i] == NULL) {
            return;
        }
    }

    sort_column = index;
    qsort(list, row_count, sizeof(int *), compare_rows);
}

int main(void) {
    size_t rows = 4;
    size_t cols = 3;
    int **list = malloc(rows * sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    int data[4][3] = {
        {3, 2, 1},
        {1, 5, 4},
        {2, 8, 6},
        {0, 3, 7}
    };

    for (size_t i = 0; i < rows; ++i) {
        list[i] = malloc(cols * sizeof(*list[i]));
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < cols; ++j) {
            list[i][j] = data[i][j];
        }
    }

    size_t sort_index = 1;
    sort_list_of_lists(list, rows, cols, sort_index);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < rows; ++i) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}