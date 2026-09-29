#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (n == 0 && k == 0) {
        return 1;
    }
    if (n == 1 && k == 0) {
        return 0;
    }
    unsigned long long *dp = (unsigned long long *)malloc((k + 1) * sizeof(unsigned long long));
    if (!dp) {
        exit(EXIT_FAILURE);
    }
    dp[0] = 0;
    if (k >= 1) {
        dp[1] = 1;
    }
    for (int i = 2; i <= n; i++) {
        unsigned long long prev = dp[0];
        dp[0] = (i - 1) * (dp[1] + prev);
        for (int j = 1; j <= k; j++) {
            if (j > i) {
                dp[j] = 0;
                continue;
            }
            unsigned long long curr = dp[j];
            unsigned long long val1 = 0;
            unsigned long long val2 = 0;
            if (j - 1 >= 0) {
                val1 = dp[j - 1];
            }
            if (j + 1 <= k && i - 1 > 0) {
                val2 = curr;
            }
            dp[j] = val1 + (i - 1) * val2;
            prev = curr;
        }
    }
    unsigned long long result = dp[k];
    free(dp);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_n;
    errno = 0;
    long val_n = strtol(argv[1], &endptr_n, 10);
    if (errno != 0 || endptr_n == argv[1] || endptr_n[0] != '\0' || val_n < INT_MIN || val_n > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val_n;
    char *endptr_k;
    errno = 0;
    long val_k = strtol(argv[2], &endptr_k, 10);
    if (errno != 0 || endptr_k == argv[2] || endptr_k[0] != '\0' || val_k < INT_MIN || val_k > INT_MAX) {
        return EXIT_FAILURE;
    }
    int k = (int)val_k;
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}