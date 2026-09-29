#include <stdio.h>
#include <stdlib.h>

long long int countSequences(int pos, int sum, int l, int r, int n, int **dp) {
    if (sum < 0) return 0;
    if (pos == n) return 1;
    if (dp[pos][sum] != -1) return dp[pos][sum];

    long long int count = 0;
    for (int i = l; i <= r; ++i) {
        count += countSequences(pos + 1, sum + i, l, r, n, dp);
    }
    dp[pos][sum] = count;
    return count;
}

int main() {
    int n = 3;
    int l = -2;
    int r = 2;
    int range = (n * (r - l)) / 2 + 1;
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        dp[i] = (int *)calloc(range, sizeof(int));
        for (int j = 0; j < range; ++j) {
            dp[i][j] = -1;
        }
    }

    long long int result = countSequences(0, 0, l, r, n, dp);
    printf("Number of sequences: %lld\n", result);

    for (int i = 0; i < n; ++i) {
        free(dp[i]);
    }
    free(dp);
    return 0;
}