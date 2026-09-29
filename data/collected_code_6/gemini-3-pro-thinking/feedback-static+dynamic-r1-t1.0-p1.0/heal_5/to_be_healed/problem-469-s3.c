#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL(a, b) ((a) > (b) ? (a) : (b))
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  */

int max_profit(int k, const int* prices, int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'total_profit' can be reduced. [variableScope]
     */
    int total_profit = 0;
    int* profit;
    int t, i;
    /* Possible weaknesses found:
     *  The scope of the variable 'max_diff' can be reduced. [variableScope]
     */
    int max_diff, prev_profit, result;

    if (n <= 0 || k <= 0 || prices == NULL) {
        return 0;
    }

    if (k >= n / 2) {
        for (i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                total_profit += prices[i] - prices[i - 1];
            }
        }
        return total_profit;
    }

    profit = (int*)calloc((size_t)n, sizeof(int));
    if (!profit) {
        return 0;
    }

    for (t = 1; t <= k; ++t) {
        max_diff = -prices[0];
        for (i = 1; i < n; ++i) {
            prev_profit = profit[i];
            profit[i] = MAX_VAL(profit[i - 1], prices[i] + max_diff);
            max_diff = MAX_VAL(max_diff, prev_profit - prices[i]);
        }
    }

    result = profit[n - 1];
    free(profit);
    
    return result;
}

int main(void) {
    int prices[] = {2, 6, 2, 5, 0, 3};
    int n = (int)(sizeof(prices) / sizeof(prices[0]));
    int k = 2;
    
    int profit = max_profit(k, prices, n);
    
    printf("%d\n", profit);
    
    return 0;
}