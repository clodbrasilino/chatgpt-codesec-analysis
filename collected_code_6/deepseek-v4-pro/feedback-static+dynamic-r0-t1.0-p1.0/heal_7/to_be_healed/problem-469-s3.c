#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got 5
  *  test case 2 failed: expected 2, got 0
  *  test case 1 failed: expected 7, got 0
  */

int max_profit(int k, const int prices[], int n) {
    if (n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int *dp = (int *)calloc((k + 1) * n, sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int t = 1; t <= k; t++) {
        int max_diff = INT_MIN;
        for (int d = 0; d < n; d++) {
            int idx = t * n + d;

            if (d == 0) {
                dp[idx] = 0;
                max_diff = dp[(t - 1) * n + d] - prices[d];
                continue;
            }

            int candidate = dp[(t - 1) * n + (d - 1)] - prices[d - 1];
            if (candidate > max_diff) {
                max_diff = candidate;
            }

            int val1 = dp[idx - 1];
            int val2 = prices[d] + max_diff;
            dp[idx] = (val1 > val2) ? val1 : val2;
        }
    }

    int result = dp[k * n + (n - 1)];
    free(dp);
    return result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;

    int profit = max_profit(k, prices, n);
    if (profit < 0) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Maximum profit with at most %d transactions: %d\n", k, profit);
    return 0;
}