#include <stdio.h>
#include <stdlib.h>

unsigned long long catalan(unsigned int n) {
    if (n <= 1) {
        return 1;
    }

    unsigned long long *dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = 1;
    dp[1] = 1;

    for (unsigned int i = 2; i <= n; i++) {
        dp[i] = 0;
        for (unsigned int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }

    unsigned long long result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    unsigned int n = 10;
    printf("Catalan(%u) = %llu\n", n, catalan(n));
    return 0;
}