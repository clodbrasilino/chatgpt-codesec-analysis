#include <stdio.h>
#include <stdbool.h>

bool canTile(int n, int m) {
    if (n <= 2 || m <= 2) {
        return n == m;
    }
    bool dp[n+1][m+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = false;
            } else if (i == 1 && j == 1) {
                dp[i][j] = true;
            } else if (i == 2 && j == 2) {
                dp[i][j] = true;
            } else if (i < 2 || j < 2) {
                dp[i][j] = false;
            } else {
                dp[i][j] = (dp[i-1][j-1] || dp[i-1][j-2] || dp[i-2][j-1]);
            }
        }
    }
    return dp[n][m];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    if (canTile(n, m)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}