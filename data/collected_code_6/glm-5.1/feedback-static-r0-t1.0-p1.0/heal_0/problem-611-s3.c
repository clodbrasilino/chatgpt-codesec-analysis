#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_nth_column(int **tuples, int num_tuples, int tuple_size, int n) {
    if (tuples == NULL || num_tuples <= 0 || tuple_size <= 0 || n < 0 || n >= tuple_size) {
        return INT_MIN;
    }

    int max_val = tuples[0][n];

    for (int i = 1; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return INT_MIN;
        }
        if (tuples[i][n] > max_val) {
            max_val = tuples[i][n];
        }
    }

    return max_val;
}

int main(void) {
    int rows = 3;
    int cols = 3;
    int r0[] = {1, 5, 9};
    int r1[] = {2, 8, 4};
    int r2[] = {7, 3, 6};

    int **tuples = (int **)malloc(rows * sizeof(int *));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0] = r0;
    tuples[1] = r1;
    tuples[2] = r2;

    int col_n = 1;
    int max_val = find_max_nth_column(tuples, rows, cols, col_n);

    if (max_val != INT_MIN) {
        printf("%d\n", max_val);
    }

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}