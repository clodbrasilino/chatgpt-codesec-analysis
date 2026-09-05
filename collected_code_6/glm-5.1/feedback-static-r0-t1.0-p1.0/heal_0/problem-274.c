#include <stdio.h>
#include <stdlib.h>

long long sumEvenIndexBinomialCoefficients(int n) {
    if (n < 0) {
        fprintf(stderr, "Invalid input: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 2;
    }
    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            dp[j] = dp[j] + dp[j - 1];
        }
    }
    long long sum = 0;
    for (int i = 0; i <= n; i += 2) {
        sum += dp[i];
    }
    free(dp);
    return sum;
}

int main(void) {
    int n = 5;
    long long result = sumEvenIndexBinomialCoefficients(n);
    printf("%lld\n", result);
    return 0;
}