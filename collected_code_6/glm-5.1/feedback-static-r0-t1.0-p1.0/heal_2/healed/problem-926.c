#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(int n) {
    unsigned long long res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

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