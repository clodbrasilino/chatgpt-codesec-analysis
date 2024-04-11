#include <stdio.h>

#define MAX 100

int dp[MAX][MAX];

int countSeq(int n, int m) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0)
                dp[i][j] = 1;
            else if (j == 0)
                dp[i][j] = 0;
            else if (i > j)
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j / 2];
        }
    }
    return dp[n][m];
}

int main() {
    int n = 2, m = 3;
    printf("%d", countSeq(n, m));
    return 0;
}