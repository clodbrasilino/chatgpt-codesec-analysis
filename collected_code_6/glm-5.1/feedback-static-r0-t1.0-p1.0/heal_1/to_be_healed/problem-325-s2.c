#include <stdio.h>
#include <stdlib.h>

int min_squares(int n) {
    if (n <= 0) {
        return 0;
    }
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = i;
        for (int j = 1; j * j <= i; j++) {
            int val = dp[i - j * j] + 1;
            if (val < dp[i]) {
                dp[i] = val;
            }
        }
    }
    int result = dp[n];
    free(dp);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        if (scanf("%d", &n) != 1 || n < 0) {
            return EXIT_FAILURE;
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        n = atoi(argv[1]);
        if (n < 0) {
            return EXIT_FAILURE;
        }
    }
    printf("%d\n", min_squares(n));
    return EXIT_SUCCESS;
}