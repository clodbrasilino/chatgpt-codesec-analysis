#include <stdio.h>
#include <stdlib.h>

long long countSequences(int n, int k) {
    if (n < 0 || k < 0) return 0;
    long long *dp = (long long *)calloc((k + 1) * (n + 1), sizeof(long long));
    if (dp == NULL) return -1;
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0) {
                dp[i * (n + 1) + j] = 0;
            } else if (i == 1) {
                dp[i * (n + 1) + j] = 1;
            } else {
                dp[i * (n + 1) + j] = (dp[(i - 1) * (n + 1) + j] + dp[i * (n + 1) + j - 1]) % 1000000007;
            }
        }
    }
    long long result = dp[k * (n + 1) + n];
    free(dp);
    return result;
}

int main() {
    int n, k;
    printf("Enter the length of the sequence and the value: ");
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    long long result = countSequences(n, k);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("Number of sequences: %lld\n", result);
    return 0;
}