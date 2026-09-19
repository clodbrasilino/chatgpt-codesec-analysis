#include <stdio.h>
#include <stdlib.h>

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (n == 0 && k == 0) return 1;
    unsigned long long *dp = (unsigned long long *)malloc((k + 2) * sizeof(unsigned long long));
    if (!dp) exit(EXIT_FAILURE);
    dp[0] = (n == 0) ? 1 : 0;
    for (int j = 1; j <= k + 1; j++) {
        dp[j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        unsigned long long prev = dp[0];
        dp[0] = (i - 1) * (dp[0] + dp[1]);
        for (int j = 1; j <= k && j < i; j++) {
            unsigned long long curr = dp[j];
            dp[j] = dp[j - 1] + (i - 1) * prev;
            prev = curr;
        }
    }
    unsigned long long result = dp[k];
    free(dp);
    return result;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}