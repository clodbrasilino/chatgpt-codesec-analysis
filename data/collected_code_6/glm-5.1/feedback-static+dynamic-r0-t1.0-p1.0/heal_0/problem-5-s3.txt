#include <stdio.h>
#include <stdlib.h>

long long count_dominoes(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (n % 2 != 0) {
        return 0;
    }
    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    dp[0] = 1;
    dp[2] = 3;
    for (int i = 4; i <= n; i += 2) {
        dp[i] = 4 * dp[i - 2] - dp[i - 4];
    }
    long long result = dp[n];
    free(dp);
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    long long ways = count_dominoes(n);
    printf("%lld\n", ways);
    return 0;
}