#include <stdio.h>
#include <stdlib.h>

unsigned long long count_dominoes(int n) {
    if (n < 0) {
        return 0;
    }
    if (n % 2 != 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 2) {
        return 3;
    }

    unsigned long long *dp = (unsigned long long *)malloc((n / 2 + 1) * sizeof(unsigned long long));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }

    dp[0] = 1;
    dp[1] = 3;

    for (int i = 2; i <= n / 2; i++) {
        dp[i] = 4 * dp[i - 1] - dp[i - 2];
    }

    unsigned long long result = dp[n / 2];
    free(dp);

    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long ways = count_dominoes(n);
    printf("%llu\n", ways);

    return 0;
}