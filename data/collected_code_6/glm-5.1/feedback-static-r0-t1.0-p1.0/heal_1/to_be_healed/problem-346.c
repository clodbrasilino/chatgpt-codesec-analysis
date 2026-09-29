#include <stdio.h>
#include <stdlib.h>

int enitringer(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (n == 0 && k == 0) {
        return 1;
    }
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((i + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][i - j];
        }
    }
    int result = dp[n][k];
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int k = atoi(argv[2]);
    if (n < 0 || k < 0 || k > n) {
        return 1;
    }
    int result = enitringer(n, k);
    printf("%d\n", result);
    return 0;
}