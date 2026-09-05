#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

bool isSubsetSumDivisibleByM(const int *arr, size_t n, int m)
{
    if (arr == NULL || n == 0 || m <= 0) {
        return false;
    }

    bool *dp = calloc((size_t)m, sizeof(bool));
    if (dp == NULL) {
        return false;
    }

    dp[0] = true;

    for (size_t i = 0; i < n; i++) {
        bool *new_dp = malloc((size_t)m * sizeof(bool));
        if (new_dp == NULL) {
            free(dp);
            return false;
        }
        memcpy(new_dp, dp, (size_t)m * sizeof(bool));

        int mod = ((arr[i] % m) + m) % m;

        for (int j = 0; j < m; j++) {
            if (dp[j]) {
                int new_sum = (j + mod) % m;
                new_dp[new_sum] = true;
            }
        }

        free(dp);
        dp = new_dp;
    }

    bool result = dp[0];
    free(dp);
    return result;
}

int main(void)
{
    int arr[] = {3, 1, 7, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int m = 6;

    if (isSubsetSumDivisibleByM(arr, n, m)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}