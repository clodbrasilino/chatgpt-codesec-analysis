#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_subset_sum(const int *set, int n, int sum) {
    if (set == NULL || n <= 0) {
        return 0;
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((sum + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int j = 1; j <= sum; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (set[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int result = dp[n][sum];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(set) / sizeof(set[0]);

    if (is_subset_sum(set, n, sum)) {
        printf("Found a subset with given sum\n");
    } else {
        printf("No subset with given sum\n");
    }

    return 0;
}