#include <stdio.h>

long long get_lobb(int m, int n)
{
    long long dp[2*n + 1][n + 1];

    for (int i = 0; i <= 2*n; i++) {
        for (int j = 0; (j <= n && j <= i); j++) {
            if (j == 0 || j == i) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }

    return dp[2*n][n] / (n + 1) * 2 * m;
}

int main()
{
    int m, n;

    printf("Enter a value for m: ");
    scanf("%d", &m);
    printf("Enter a value for n: ");
    scanf("%d", &n);

    printf("The Lobb number L(%d, %d) is: %lld\n", m, n, get_lobb(m, n));

    return 0;
}