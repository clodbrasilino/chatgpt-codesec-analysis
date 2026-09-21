#include <stdio.h>
#include <string.h>

int longest_repeating_non_overlapping_subsequence(const char *X, int m) {
    int dp[m+1][m+1];
    for (int i = 0; i <= m; i++)
        dp[i][i] = 0;
    for (int cl = 2; cl <= m; cl++) {
        for (int i = 0; i < m - cl + 1; i++) {
            int j = i + cl - 1;
            if (X[i] == X[j] && cl == 2)
                dp[i][j] = 2;
            else if (X[i] == X[j])
                dp[i][j] = dp[i+1][j-1] + 2;
            else
                dp[i][j] = (dp[i][j-1] > dp[i+1][j]) ? dp[i][j-1] : dp[i+1][j];
        }
    }
    int res = dp[0][m-1];
    return res > 0 ? res / 2 : 0;
}

int main() {
    const char X[] = "AABEBCDD";
    int n = strlen(X);
    printf("The length of the longest repeating non-overlapping subsequence is %d\n", longest_repeating_non_overlapping_subsequence(X, n));
    return 0;
}