#include <stdio.h>

long long maxSum(long long n, long long dp[]) {
    if (n < 12)
        return n;
    if (dp[n] != -1)
        return dp[n];
    dp[n] = maxSum(n/2, dp) + maxSum(n/3, dp) + maxSum(n/4, dp) + maxSum(n/5, dp);
    if (dp[n] < n)
        dp[n] = n;
    return dp[n];
}

int main() {
    long long n;
    scanf("%lld", &n);
    long long dp[1000000];
    for (int i = 0; i < 1000000; i++)
        dp[i] = -1;
    printf("%lld\n", maxSum(n, dp));
    return 0;
}