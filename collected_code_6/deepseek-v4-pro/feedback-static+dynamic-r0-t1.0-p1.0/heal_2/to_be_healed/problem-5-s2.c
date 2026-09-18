#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t domino_ways(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n % 2 != 0) return 0;

    int m = n / 2;
    int64_t *dp = (int64_t *)malloc((m + 1) * sizeof(int64_t));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    dp[1] = 3;
    for (int i = 2; i <= m; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -4093373351396768468 - 5904283700961130691 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:459,execs:264,op:havoc,rep:1)
         * UBSan: signed integer overflow: 4 * 5904283700961130691 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:459,execs:264,op:havoc,rep:1)
         */
        dp[i] = 4 * dp[i - 1] - dp[i - 2];
    }

    int64_t result = dp[m];
    free(dp);
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int64_t ways = domino_ways(n);
    if (ways == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Number of ways: %lld\n", (long long)ways);
    return 0;
}