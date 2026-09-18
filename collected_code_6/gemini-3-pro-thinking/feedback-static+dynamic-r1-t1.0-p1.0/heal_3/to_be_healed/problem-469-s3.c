#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  */

/* Possible weaknesses found:
 *  Parameter 'prices' can be declared as pointer to const [constParameterPointer]
 */
int max_profit(int k, int* prices, int n) {
    if (n <= 0 || k <= 0) {
        return 0;
    }

    int* profit = (int*)calloc(n, sizeof(int));
    if (!profit) {
        return 0;
    }

    for (int t = 1; t <= k; ++t) {
        int max_diff = -prices[0];
        for (int i = 1; i < n; ++i) {
            int prev_profit = profit[i];
            profit[i] = max(profit[i - 1], prices[i] + max_diff);
            max_diff = max(max_diff, prev_profit - prices[i]);
        }
    }

    int result = profit[n - 1];
    free(profit);
    
    return result;
}

int main(void) {
    int prices[] = {2, 6, 2, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    
    int profit = max_profit(k, prices, n);
    
    printf("%d\n", profit);
    
    return 0;
}