#include <stdio.h>
#include <stdlib.h>

int calculate_max_sum(const int *triangle, size_t rows, int *max_sum) {
    if (triangle == NULL || max_sum == NULL || rows == 0) {
        return -1;
    }

    size_t total_elements = (rows * (rows + 1)) / 2;
    int *dp = (int *)malloc(total_elements * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i < total_elements; ++i) {
        dp[i] = triangle[i];
    }

    for (size_t i = rows - 1; i > 0; --i) {
        size_t current_row_start = (i * (i + 1)) / 2;
        size_t prev_row_start = ((i - 1) * i) / 2;

        for (size_t j = 0; j < i; ++j) {
            int left = dp[current_row_start + j];
            int right = dp[current_row_start + j + 1];
            int greater_child = (left > right) ? left : right;
            dp[prev_row_start + j] += greater_child;
        }
    }

    *max_sum = dp[0];
    free(dp);

    return 0;
}

int main(void) {
    const int triangle[] = {
        3,
        7, 4,
        2, 4, 6,
        8, 5, 9, 3
    };

    size_t rows = 4;
    int max_sum = 0;

    if (calculate_max_sum(triangle, rows, &max_sum) == 0) {
        printf("%d\n", max_sum);
    } else {
        fprintf(stderr, "Error processing the triangle.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}