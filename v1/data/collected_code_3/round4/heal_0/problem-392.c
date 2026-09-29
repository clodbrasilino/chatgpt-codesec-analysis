#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

long long int dp[MAX];

long long int maxSum(long long int n) {
    if (n < 12)
        return n;
    if (n < MAX && dp[n] != 0)
        return dp[n];
    long long int temp = maxSum(n/2) + maxSum(n/3) + maxSum(n/4) + maxSum(n/5);
    if (n < MAX)
        dp[n] = temp;
    return temp;
}

int main() {
    long long int n;
    while (scanf("%lld", &n) != EOF) {
        printf("%lld\n", maxSum(n));
    }
    return 0;
}