#include <stdio.h>
#include <stdlib.h>

int max_profit(int k, const int prices[], int n)
{
    int *prev;
    int *curr;
    int *tmp;
    int result;
    int val;
    int i;
    int t;

    if (prices == NULL || n < 0 || k < 0) {
        return -1;
    }
    if (n <= 1 || k == 0) {
        return 0;
    }

    if (k >= n / 2) {
        int profit = 0;
        for (i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    prev = calloc((size_t)n, sizeof(*prev));
    if (prev == NULL) {
        return -1;
    }

    curr = calloc((size_t)n, sizeof(*curr));
    if (curr == NULL) {
        free(prev);
        return -1;
    }

    for (t = 0; t < k; t++) {
        int max_diff = prev[0] - prices[0];
        curr[0] = 0;

        for (i = 1; i < n; i++) {
            val = prices[i] + max_diff;
            curr[i] = (curr[i - 1] > val) ? curr[i - 1] : val;

            val = prev[i] - prices[i];
            if (val > max_diff) {
                max_diff = val;
            }
        }

        tmp = prev;
        prev = curr;
        curr = tmp;
    }

    result = prev[n - 1];

    free(prev);
    free(curr);

    return result;
}

int main(void)
{
    int prices[] = {100, 180, 260, 310, 40, 535, 695};
    int k = 2;
    int n = (int)(sizeof(prices) / sizeof(prices[0]));
    int profit;

    profit = max_profit(k, prices, n);
    if (profit < 0) {
        printf("Error: invalid input or allocation failure\n");
        return 1;
    }

    printf("Maximum profit: %d\n", profit);
    return 0;
}