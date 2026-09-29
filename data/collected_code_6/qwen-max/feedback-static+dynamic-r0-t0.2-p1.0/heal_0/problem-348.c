#include <stdio.h>
#include <stdlib.h>

long long countSequences(int n, int k) {
    long long dp[k + 1][n + 1];
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (i == 1) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 1000000007;
            }
        }
    }
    return dp[k][n];
}

int main() {
    int n, k;
    printf("Enter the length of the sequence and the number of values: ");
    scanf("%d %d", &n, &k);
    long long result = countSequences(n, k);
    printf("Number of sequences: %lld\n", result);
    return 0;
}