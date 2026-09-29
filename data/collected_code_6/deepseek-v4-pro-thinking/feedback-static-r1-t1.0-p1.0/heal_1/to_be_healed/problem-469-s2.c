#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'prices' can be declared as const array [constParameter]
 */
int maxProfit(int k, int prices[], int n) {
    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int *dp_prev = (int *)calloc((size_t)n, sizeof(int));
    int *dp_curr = (int *)calloc((size_t)n, sizeof(int));
    if (dp_prev == NULL || dp_curr == NULL) {
        free(dp_prev);
        free(dp_curr);
        return -1;
    }

    for (int t = 1; t <= k; ++t) {
        int maxDiff = -prices[0];
        dp_curr[0] = 0;
        for (int d = 1; d < n; ++d) {
            dp_curr[d] = dp_curr[d - 1];
            int candidate = prices[d] + maxDiff;
            if (candidate > dp_curr[d]) {
                dp_curr[d] = candidate;
            }
            int diff = dp_prev[d] - prices[d];
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }
        int *tmp = dp_prev;
        dp_prev = dp_curr;
        dp_curr = tmp;
    }

    int result = dp_prev[n - 1];
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