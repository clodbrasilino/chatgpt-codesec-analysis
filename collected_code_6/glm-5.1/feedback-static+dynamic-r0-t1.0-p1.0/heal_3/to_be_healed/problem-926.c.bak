#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(int n) {
    unsigned long long res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 8
  *  test case 0 failed: expected 924, got 8680820740572828304
  *  test case 1 failed: expected 2, got 8
  */

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (n == 0 && k == 0) return 1;
    if (k == 0) {
        unsigned long long sub_factorial = 1;
        for (int i = 2; i <= n; i++) {
            sub_factorial = (i - 1) * (sub_factorial + factorial(i - 1));
        }
        return sub_factorial;
    }
    unsigned long long *dp = (unsigned long long *)malloc((k + 1) * sizeof(unsigned long long));
    if (!dp) exit(EXIT_FAILURE);
    dp[0] = 0;
    if (k >= 1) dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long prev = dp[0];
        if (k >= 1) {
            dp[0] = (i - 1) * (dp[1] + prev);
        }
        for (int j = 1; j <= k; j++) {
            unsigned long long curr = dp[j];
            if (j == 1) {
                dp[j] = (i - 1) * dp[j - 1];
            } else {
                dp[j] = dp[j - 1] + (i - 1) * curr;
            }
            /* Possible weaknesses found:
             *  Variable 'prev' is assigned a value that is never used. [unreadVariable]
             */
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
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}