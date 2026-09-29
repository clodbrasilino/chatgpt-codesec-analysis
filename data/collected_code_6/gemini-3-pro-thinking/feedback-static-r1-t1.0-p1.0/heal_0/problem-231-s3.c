#include <stdio.h>
#include <stdlib.h>

int find_maximum_sum(const int **triangle, int num_rows, int *out_max_sum);

int find_maximum_sum(const int **triangle, int num_rows, int *out_max_sum) {
    if (!triangle || num_rows <= 0 || !out_max_sum) {
        return -1;
    }

    for (int i = 0; i < num_rows; i++) {
        if (!triangle[i]) {
            return -1;
        }
    }

    int *dp = (int *)malloc((size_t)num_rows * sizeof(int));
    if (!dp) {
        return -1;
    }

    for (int c = 0; c < num_rows; c++) {
        dp[c] = triangle[num_rows - 1][c];
    }

    for (int r = num_rows - 2; r >= 0; r--) {
        for (int c = 0; c <= r; c++) {
            int left = dp[c];
            int right = dp[c + 1];
            dp[c] = triangle[r][c] + (left > right ? left : right);
        }
    }

    *out_max_sum = dp[0];
    free(dp);

    return 0;
}

int main(void) {
    const int row0[] = {3};
    const int row1[] = {7, 4};
    const int row2[] = {2, 4, 6};
    const int row3[] = {8, 5, 9, 3};

    const int *triangle[] = {
        row0,
        row1,
        row2,
        row3
    };

    int num_rows = 4;
    int max_sum = 0;

    int status = find_maximum_sum(triangle, num_rows, &max_sum);
    
    if (status == 0) {
        printf("%d\n", max_sum);
    } else {
        fprintf(stderr, "Error calculating maximum sum\n");
    }

    return status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}