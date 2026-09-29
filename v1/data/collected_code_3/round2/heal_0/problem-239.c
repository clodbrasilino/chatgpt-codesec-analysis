#include <stdio.h>

#define MAX 100

int dp[MAX][MAX];

int numSeq(int n, int m) {
    if (n == 0)
        return 1;
    if (m == 0)
        return 0;
    if (dp[n][m] != -1)
        return dp[n][m];
    int include = numSeq(n - 1, m / 2);
    int exclude = numSeq(n, m - 1);
    dp[n][m] = include + exclude;
    return dp[n][m];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            dp[i][j] = -1;
    printf("%d\n", numSeq(n, m));
    return 0;
}