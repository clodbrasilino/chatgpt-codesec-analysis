#include <stdio.h>
#include <stdlib.h>

int checkSubsetDivisibleByM(int arr[], int n, int m) {
    if (m == 1) {
        return 1;
    }

    int *dp = (int *)malloc(m * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < m; ++i) {
        dp[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (dp[0]) {
            free(dp);
            return 1;
        }

        int *temp = (int *)malloc(m * sizeof(int));
        if (temp == NULL) {
            free(dp);
            return -1;
        }

        for (int j = 0; j < m; ++j) {
            temp[j] = 0;
        }

        for (int j = 0; j < m; ++j) {
            if (dp[j]) {
                if (!dp[(j + arr[i]) % m]) {
                    temp[(j + arr[i]) % m] = 1;
                }
            }
        }

        for (int j = 0; j < m; ++j) {
            if (temp[j]) {
                dp[j] = 1;
            }
        }

        dp[arr[i] % m] = 1;

        free(temp);
    }

    int result = dp[0];
    free(dp);
    return result;
}

int main() {
    int arr[] = {3, 1, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = 5;

    int res = checkSubsetDivisibleByM(arr, n, m);
    printf("%d\n", res);

    return 0;
}