#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'gold' can be declared as pointer to const [constParameterPointer]
 */
int getMaxGold(int *gold, int n, int m) {
    if (n <= 0 || m <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * m * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i * m] = gold[i * m];
    }

    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            int right = dp[i * m + (j - 1)];
            int right_up = (i == 0) ? 0 : dp[(i - 1) * m + (j - 1)];
            int right_down = (i == n - 1) ? 0 : dp[(i + 1) * m + (j - 1)];
            dp[i * m + j] = gold[i * m + j] + max(right, max(right_up, right_down));
        }
    }

    int max_gold = 0;
    for (int i = 0; i < n; i++) {
        max_gold = max(max_gold, dp[i * m + (m - 1)]);
    }

    free(dp);
    return max_gold;
}

int main(void) {
    int n = 4;
    int m = 4;
    int gold[16] = {
        1, 3, 1, 5,
        2, 2, 4, 1,
        5, 0, 2, 3,
        0, 6, 1, 2
    };

    int result = getMaxGold(gold, n, m);
    printf("%d\n", result);

    return 0;
}