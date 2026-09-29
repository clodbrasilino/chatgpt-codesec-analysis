#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 26, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  *  test case 1 failed: expected 11, got <no output>
  */

int64_t eulerian_number(int n, int m) {
    if (m < 0 || n < 0 || m > n) {
        return 0;
    }

    if (n == 0) {
        return 1;
    }

    if (m >= n) {
        return 0;
    }

    if ((size_t)n > SIZE_MAX / sizeof(int64_t) - 1) {
        return -1;
    }

    int64_t *dp = (int64_t*)calloc((size_t)n + 1, sizeof(int64_t));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            int64_t term1 = (int64_t)(i - j) * dp[j - 1];
            int64_t term2 = (int64_t)(j + 1) * dp[j];

            if ((i - j) != 0 && dp[j - 1] != 0 && term1 / dp[j - 1] != (i - j)) {
                free(dp);
                return -1;
            }
            if (dp[j] != 0 && term2 / dp[j] != (j + 1)) {
                free(dp);
                return -1;
            }

            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 6795622177941569380 + 4663059128687439720 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:434,execs:228,op:havoc,rep:2)
             */
            int64_t sum = term1 + term2;
            if ((term1 > 0 && term2 > 0 && sum < 0) || (term1 < 0 && term2 < 0 && sum > 0)) {
                free(dp);
                return -1;
            }

            dp[j] = sum;
        }
        dp[0] = 1;
    }

    int64_t result = dp[m];
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

    int64_t result = eulerian_number(n, m);
    if (result < 0) {
        fprintf(stderr, "Overflow or memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("A(%d, %d) = %" PRId64 "\n", n, m, result);
    return EXIT_SUCCESS;
}