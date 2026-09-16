#include <stdio.h>
#include <stdlib.h>

int isSubsetSum(const int set[], int n, int sum) {
    int *dp = (int *)malloc((n + 1) * (sum + 1) * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= n; i++) {
        dp[i * (sum + 1)] = 1;
    }
    for (int i = 1; i <= sum; i++) {
        dp[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                dp[i * (sum + 1) + j] = dp[(i - 1) * (sum + 1) + j];
            } else {
                dp[i * (sum + 1) + j] = dp[(i - 1) * (sum + 1) + j] || dp[(i - 1) * (sum + 1) + (j - set[i - 1])];
            }
        }
    }

    int result = dp[n * (sum + 1) + sum];
    free(dp);

    return result;
}

int main() {
    const int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(set) / sizeof(set[0]);

    if (isSubsetSum(set, n, sum)) {
        printf("Found a subset with given sum\n");
    } else {
        printf("No subset with given sum\n");
    }

    return 0;
}