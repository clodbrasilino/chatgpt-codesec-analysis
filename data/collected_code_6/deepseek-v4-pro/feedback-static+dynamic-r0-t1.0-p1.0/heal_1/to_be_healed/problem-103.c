#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got <no output>
  *  test case 2 failed: expected 26, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  */

long long eulerian_number(int n, int m) {
    /* Possible weaknesses found:
     *  Assuming that condition 'm>=n' is not redundant
     */
    if (m < 0 || n < 0 || m >= n) {
        return 0;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'n==0' is not redundant
     */
    if (n == 0) {
        /* Possible weaknesses found:
         *  Condition 'm==0' is always false [knownConditionTrueFalse]
         *  Condition 'm==0' is always false
         */
        return m == 0 ? 1 : 0;
    }

    long long *dp = (long long*)calloc((size_t)n + 1, sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            dp[j] = (i - j) * dp[j - 1] + (j + 1) * dp[j];
        }
        dp[0] = 1;
    }

    long long result = dp[m];
    free(dp);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:405,execs:285,op:havoc,rep:14; likely memory-safety defect
  */

int main(void) {
    int n, m;
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = eulerian_number(n, m);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("A(%d, %d) = %lld\n", n, m, result);
    return EXIT_SUCCESS;
}