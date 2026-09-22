#include <stdio.h>
#include <stdlib.h>

long long int countSequences(long a, long b, long c, long d, long n) {
    long long int dp[64][n+1];
    for (long i = 0; i <= n ; i++)
        dp[0][i] = 0;
    for (long i = 1; i <= 63; i++)
        dp[i][0] = 1;
    for (long i = 1; i <= 63; i++){
        for (long j = 1; j <= n; j++) {
            dp[i][j] = dp[i-1][j] + (j>=a?dp[i][j-a]:0) + (j>=b?dp[i][j-b]:0) + (j>=c?dp[i][j-c]:0) + (j>=d?dp[i][j-d]:0);
        }
    }
    return dp[63][n];
}

int main() {
    long a = 1, b = 2, c = 3, d = 4, n = 5;
    printf("%lld\n", countSequences(a, b, c, d, n));
    return 0;
}