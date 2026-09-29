#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

long long eulerian_number(int n, int m) {
    if (n == 0) {
        return m == 0 ? 1 : 0;
    }
    if (m < 0 || m >= n) {
        return 0;
    }

    long long *dp = (long long*)calloc((size_t)n + 1, sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            if (dp[j - 1] > 0 && (i - j) > LLONG_MAX / dp[j - 1]) {
                free(dp);
                return -2;
            }
            long long term1 = (i - j) * dp[j - 1];

            if (dp[j] > 0 && (j + 1) > LLONG_MAX / dp[j]) {
                free(dp);
                return -2;
            }
            long long term2 = (j + 1) * dp[j];

            if (term1 > 0 && term2 > LLONG_MAX - term1) {
                free(dp);
                return -2;
            }
            dp[j] = term1 + term2;
        }
        dp[0] = 1;
    }

    long long result = dp[m];
    free(dp);
    return result;
}

int main(void) {
    int n, m;
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = eulerian_number(n, m);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (result == -2) {
        fprintf(stderr, "Integer overflow detected\n");
        return EXIT_FAILURE;
    }

    printf("A(%d, %d) = %lld\n", n, m, result);
    return EXIT_SUCCESS;
}