#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got 0
  *  test case 1 failed: expected 7, got 0
  *  test case 0 failed: expected 10, got 5
  */

int maxProfit(int k, const int prices[], int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'maxDiff' can be reduced. [variableScope]
     *  The scope of the variable 'profit' can be reduced. [variableScope]
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int profit, i, t, d, maxDiff, candidate, diff, result;
    int *dp_prev, *dp_curr, *tmp;

    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
        profit = 0;
        for (i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    dp_prev = (int *)calloc((size_t)n, sizeof(int));
    dp_curr = (int *)calloc((size_t)n, sizeof(int));
    if (dp_prev == NULL || dp_curr == NULL) {
        free(dp_prev);
        free(dp_curr);
        return -1;
    }

    for (t = 1; t <= k; ++t) {
        maxDiff = -prices[0];
        dp_curr[0] = 0;
        for (d = 1; d < n; ++d) {
            dp_curr[d] = dp_curr[d - 1];
            candidate = prices[d] + maxDiff;
            if (candidate > dp_curr[d]) {
                dp_curr[d] = candidate;
            }
            diff = dp_prev[d] - prices[d];
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }
        tmp = dp_prev;
        dp_prev = dp_curr;
        dp_curr = tmp;
    }

    result = dp_prev[n - 1];
    free(dp_prev);
    free(dp_curr);
    return result;
}

int main(void) {
    int prices[] = {2, 5, 7, 1, 4, 3, 1, 3};
    int n = (int)(sizeof(prices) / sizeof(prices[0]));
    int k = 3;
    int result = maxProfit(k, prices, n);
    printf("%d\n", result);
    return 0;
}