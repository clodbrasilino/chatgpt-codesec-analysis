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
                int mod_val = (j + arr[i]) % m;
                if (mod_val < 0) {
                    mod_val += m;
                }
                if (dp[mod_val] == false) {
                    temp[mod_val] = true;
                }
            }
        }

        for (int j = 0; j < m; j++) {
            if (temp[j]) {
                dp[j] = true;
            }
        }

        int mod_arr_val = arr[i] % m;
        if (mod_arr_val < 0) {
            mod_arr_val += m;
        }
        dp[mod_arr_val] = true;
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