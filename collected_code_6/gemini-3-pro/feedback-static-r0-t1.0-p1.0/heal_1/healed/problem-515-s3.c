#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool hasSubsetSumDivisibleByM(const int arr[], int n, int m) {
    if (n > m) {
        return true;
    }

    bool dp[m];
    for (int i = 0; i < m; i++) {
        dp[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (dp[0]) {
            return true;
        }

        bool temp[m];
        for (int j = 0; j < m; j++) {
            temp[j] = false;
        }

        for (int j = 0; j < m; j++) {
            if (dp[j]) {
                if (dp[(j + arr[i]) % m] == false) {
                    temp[(j + arr[i]) % m] = true;
                }
            }
        }

        for (int j = 0; j < m; j++) {
            if (temp[j]) {
                dp[j] = true;
            }
        }

        dp[arr[i] % m] = true;
    }

    return dp[0];
}

int main() {
    int arr[] = {3, 1, 4, 2, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = 5;

    if (hasSubsetSumDivisibleByM(arr, n, m)) {
        printf("There is a subset with sum divisible by %d\n", m);
    } else {
        printf("There is no subset with sum divisible by %d\n", m);
    }

    return 0;
}