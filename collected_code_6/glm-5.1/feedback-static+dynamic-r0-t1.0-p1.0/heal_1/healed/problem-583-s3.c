#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "n must be a non-negative integer within valid range\n");
        return 1;
    }

    int n = (int)val;
    unsigned long long result = catalan_number(n);
    printf("%llu\n", result);

    return 0;
}