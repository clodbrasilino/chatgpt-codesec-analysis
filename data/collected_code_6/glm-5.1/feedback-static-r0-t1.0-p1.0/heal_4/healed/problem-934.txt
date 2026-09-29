#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long find_delannoy(int n) {
    if (n < 0) {
        return 0;
    }
    unsigned long long *dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (!dp) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            dp[i] += 2ULL * dp[j] * dp[i - 1 - j];
        }
    }
    unsigned long long result = dp[n];
    free(dp);
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX || errno == ERANGE) {
        fprintf(stderr, "n must be a non-negative integer within valid range\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    unsigned long long result = find_delannoy(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}