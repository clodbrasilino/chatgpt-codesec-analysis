#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

long long int dp[MAX];

long long int max_func(long long int a, long long int b);
long long int max_sum(long long int n);

long long int max_func(long long int a, long long int b) {
    return (a > b) ? a : b;
}

long long int max_sum(long long int n) {
    if (n < MAX) {
        return dp[n];
    }
    else {
        return max_func(n, max_sum(n/2) + max_sum(n/3) + max_sum(n/4) + max_sum(n/5));
    }
}

int main() {
    long long int n;
    for (n = 0; n < MAX; n++) {
        if (n <= 11) {
            dp[n] = n;
        }
        else {
            dp[n] = max_func(n, dp[n/2] + dp[n/3] + dp[n/4] + dp[n/5]);
        }
    }
    while (scanf("%lld", &n) != EOF) {
        printf("%lld\n", max_sum(n));
    }
    return 0;
}