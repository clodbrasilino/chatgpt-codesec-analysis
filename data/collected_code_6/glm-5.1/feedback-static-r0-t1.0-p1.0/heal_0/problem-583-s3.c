#include <stdio.h>
#include <stdlib.h>

unsigned long long catalan_number(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long *dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
        for (int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }

    unsigned long long result = dp[n];
    free(dp);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0) {
        fprintf(stderr, "n must be a non-negative integer\n");
        return 1;
    }

    unsigned long long result = catalan_number(n);
    printf("%llu\n", result);

    return 0;
}