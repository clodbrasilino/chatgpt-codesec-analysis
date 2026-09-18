#include <stdio.h>
#include <stdlib.h>

int countSubsequences(int* arr, int n, int k) {
    if (k <= 1) {
        return 0;
    }

    int count = 0;
    int dp[k];
    for (int i = 0; i < k; i++) {
        dp[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int val = arr[i];
        if (val == 0) {
            count += 1;
            continue;
        }
        if (val < k) {
            int temp[k];
            for (int j = 0; j < k; j++) {
                temp[j] = dp[j];
            }
            for (int j = 1; j < k; j++) {
                if (dp[j] > 0 && j * val < k) {
                    temp[j * val] += dp[j];
                }
            }
            temp[val] += 1;
            for (int j = 0; j < k; j++) {
                dp[j] = temp[j];
            }
        }
    }

    for (int i = 1; i < k; i++) {
        count += dp[i];
    }

    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 10;

    int result = countSubsequences(arr, n, k);
    printf("%d\n", result);

    return 0;
}