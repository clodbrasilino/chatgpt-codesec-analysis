#include <stdio.h>
#include <stdlib.h>

int count_sequences(int n, int m) {
    if (n == 0) return 1;
    int dp[n + 1][m + 1];
    for (int j = 1; j <= m; ++j) dp[1][j] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = 0;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k * 2 <= j; ++k)
                dp[i][j] += dp[i - 1][k];
    int result = 0;
    for (int j = 1; j <= m; ++j)
        result += dp[n][j];
    return result;
}

int main() {
    int n, m;
    printf("Enter the length of the sequence (n): ");
    scanf("%d", &n);
    printf("Enter the maximum value in the sequence (m): ");
    scanf("%d", &m);
    int result = count_sequences(n, m);
    printf("Number of sequences: %d\n", result);
    return 0;
}