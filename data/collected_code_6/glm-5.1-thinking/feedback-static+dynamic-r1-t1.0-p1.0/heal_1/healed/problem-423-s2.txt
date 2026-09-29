#include <stdio.h>
#include <stdlib.h>

static int max(int a, int b, int c) {
    int m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    return m;
}

int solve_gold_mine(const int *gold, int n, int m) {
    if (n <= 0 || m <= 0) {
        return 0;
    }

    size_t total_size = (size_t)n * m;
    if (total_size == 0) {
        return 0;
    }

    int *dp = malloc(total_size * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i * m] = gold[i * m];
    }

    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            int right_up = (i == 0) ? 0 : dp[(i - 1) * m + j - 1];
            int right = dp[i * m + j - 1];
            int right_down = (i == n - 1) ? 0 : dp[(i + 1) * m + j - 1];

            dp[i * m + j] = gold[i * m + j] + max(right_up, right, right_down);
        }
    }

    int max_gold = dp[m - 1];
    for (int i = 1; i < n; i++) {
        if (dp[i * m + m - 1] > max_gold) {
            max_gold = dp[i * m + m - 1];
        }
    }

    free(dp);
    return max_gold;
}

int main(void) {
    const int gold[] = {1, 3, 1, 5, 2, 2, 4, 1, 5, 0, 2, 3, 0, 6, 1, 2};
    int n = 4;
    int m = 4;
    int result = solve_gold_mine(gold, n, m);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}