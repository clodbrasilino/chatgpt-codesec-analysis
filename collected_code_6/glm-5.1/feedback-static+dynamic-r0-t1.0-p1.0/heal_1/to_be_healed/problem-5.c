#include <stdio.h>
#include <stdlib.h>

long long count_dominoes(int n) {
    if (n < 0) {
        return 0;
    }
    if (n % 2 != 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    dp[0] = 1;
    dp[2] = 3;
    for (int i = 4; i <= n; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4 * 5904283700961130691 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:750,execs:472,op:havoc,rep:3)
         * UBSan: signed integer overflow: -4093373351396768468 - 5904283700961130691 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:750,execs:472,op:havoc,rep:3)
         */
        dp[i] = 4 * dp[i - 2] - dp[i - 4];
    }
    long long result = dp[n];
    free(dp);
    dp = NULL;
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    long long result = count_dominoes(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}