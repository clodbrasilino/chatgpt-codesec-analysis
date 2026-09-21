#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

bool isSubsetSumDivisibleByM(const int *arr, size_t n, int m)
{
    if (arr == NULL || n == 0 || m <= 0) {
        return false;
    }

    if ((size_t)m > SIZE_MAX / sizeof(bool)) {
        return false;
    }

    size_t size = (size_t)m * sizeof(bool);

    bool *dp = calloc((size_t)m, sizeof(bool));
    if (dp == NULL) {
        return false;
    }

    bool *new_dp = calloc((size_t)m, sizeof(bool));
    if (new_dp == NULL) {
        free(dp);
        return false;
    }

    dp[0] = true;

    for (size_t i = 0; i < n; i++) {
        if (size > 0 && size <= SIZE_MAX) {
            void *memcpy_result = memcpy(new_dp, dp, size);
            if (memcpy_result == NULL) {
                free(dp);
                free(new_dp);
                return false;
            }
        }

        int mod = ((arr[i] % m) + m) % m;

        for (int j = 0; j < m; j++) {
            if (dp[j]) {
                int new_sum = (j + mod) % m;
                if (new_sum >= 0 && new_sum < m) {
                    new_dp[new_sum] = true;
                }
            }
        }

        bool *temp = dp;
        dp = new_dp;
        new_dp = temp;
    }

    bool result = dp[0];
    free(dp);
    free(new_dp);
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