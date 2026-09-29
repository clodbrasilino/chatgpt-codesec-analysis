#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected True, got 0
  */

/* Possible weaknesses found:
 *  Parameter 'set' can be declared as const array [constParameter]
 */
int isSubsetSum(int set[], int n, int sum) {
    int subset[n + 1][sum + 1];
    for (int i = 0; i <= n; i++) {
        subset[i][0] = 1;
    }
    for (int i = 1; i <= sum; i++) {
        subset[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                subset[i][j] = subset[i - 1][j];
            } else {
                if (subset[i - 1][j] || subset[i - 1][j - set[i - 1]]) {
                    subset[i][j] = 1;
                } else {
                    subset[i][j] = 0;
                }
            }
        }
    }
    return subset[n][sum];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int n = argc - 2;
    int *set = (int *)malloc(n * sizeof(int));
    if (set == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        set[i] = atoi(argv[i + 1]);
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int sum = atoi(argv[argc - 1]);
    if (sum < 0) {
        free(set);
        return 1;
    }
    int result = isSubsetSum(set, n, sum);
    printf("%d\n", result);
    free(set);
    return 0;
}