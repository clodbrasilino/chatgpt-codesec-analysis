#include <stdio.h>
#include <stdlib.h>

unsigned long long entiringer(unsigned int n, unsigned int k) {
    if (n == 0 && k == 0) {
        return 1;
    }
    if (k >= n || n == 0) {
        return 0;
    }
    unsigned long long *dp = (unsigned long long *)malloc(n * sizeof(unsigned long long));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    dp[0] = 1;
    for (unsigned int i = 1; i < n; i++) {
        dp[i] = 0;
    }
    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int j = 1; j < i; j++) {
            dp[j] = dp[j] + dp[j - 1];
        }
        dp[i] = 0;
    }
    unsigned long long result = dp[k];
    free(dp);
    return result;
}

int main(void) {
    unsigned int n = 4;
    unsigned int k = 2;
    unsigned long long result = entiringer(n, k);
    printf("%llu\n", result);
    return 0;
}