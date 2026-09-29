#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'set' can be declared as pointer to const [constParameterPointer]
 */
int is_subset_sum(int *set, int n, int sum) {
    int **dp;
    int i, j;
    int result;

    if (set == NULL && n > 0) {
        return 0;
    }

    if (sum < 0) {
        return 0;
    }

    dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((sum + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (i = 0; i <= n; i++) {
        for (j = 0; j <= sum; j++) {
            if (j == 0) {
                dp[i][j] = 1;
            } else if (i == 0) {
                dp[i][j] = 0;
            } else if (set[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    result = dp[n][sum];

    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int set1[] = {3, 34, 4, 12, 5, 2};
    int n1 = sizeof(set1) / sizeof(set1[0]);
    int sum1 = 9;

    int set2[] = {3, 34, 4, 12, 5, 2};
    int n2 = sizeof(set2) / sizeof(set2[0]);
    int sum2 = 30;

    printf("Subset with sum %d exists: %s\n", sum1, 
           is_subset_sum(set1, n1, sum1) ? "Yes" : "No");
    printf("Subset with sum %d exists: %s\n", sum2, 
           is_subset_sum(set2, n2, sum2) ? "Yes" : "No");

    return 0;
}