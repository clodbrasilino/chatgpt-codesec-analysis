#include <stdio.h>
#include <stdlib.h>

int count_sequences(long long arr[], int n, int k, long long dp[51][51][201]) {
    if (n == 0) {
        return k == 0 ? 1 : 0;
    }
    int offset = 100 + arr[0];
    if (k + 100 >= 0 && k + 100 < 201 && offset >= 0 && offset < 201 && dp[n-1][k+100][offset] != -1) {
        return dp[n-1][k+100][offset];
    }
    if (arr[0] > k) {
        dp[n-1][k+100][offset] = count_sequences(arr + 1, n - 1, k, dp);
    } else {
        int offset2 = 100 + k - arr[0];
        if (offset2 >= 0 && offset2 < 201) {
            dp[n-1][k+100][offset] = (count_sequences(arr + 1, n - 1, k - arr[0], dp) +
                                     count_sequences(arr + 1, n - 1, k, dp)) % 1000000007;
        } else {
            dp[n-1][k+100][offset] = 0;
        }
    }
    return dp[n-1][k+100][offset];
}

int main() {
    long long arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k_target;

    printf("Enter the length of the sequence: ");
    if (scanf("%d", &k_target) != 1 || k_target < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    long long dp[51][51][201];
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 51; ++j) {
            for (int k = 0; k < 201; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }

    int result = count_sequences(arr, n, k_target, dp);
    printf("Total sequences: %d\n", result);

    return 0;
}