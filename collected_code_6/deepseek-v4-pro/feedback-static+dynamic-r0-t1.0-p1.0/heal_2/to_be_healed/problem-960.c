#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_N 100

int64_t count_ways(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    if (n == 2) return 2;

    int64_t *dp = (int64_t *)malloc((n + 1) * sizeof(int64_t));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7015254043203144209 + 3814116544533214284 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:1829,execs:1047,op:havoc,rep:8)
         * UBSan: signed integer overflow: -6403789537783938262 + -5543680227583415947 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:1829,execs:1047,op:havoc,rep:8)
         */
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    int64_t result = dp[n];
    free(dp);
    return result;
}

int64_t solve_tiling(int n) {
    if (n < 0) {
        fprintf(stderr, "Invalid input: n must be non-negative\n");
        return -1;
    }
    if (n > MAX_N) {
        fprintf(stderr, "Invalid input: n too large\n");
        return -1;
    }
    return count_ways(n);
}

int main(void) {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int64_t ways = solve_tiling(n);
    if (ways != -1) {
        /* Possible weaknesses found:
         *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         */
        printf("Number of ways to tile 2x%d board: %lld\n", n, ways);
    }
    return EXIT_SUCCESS;
}