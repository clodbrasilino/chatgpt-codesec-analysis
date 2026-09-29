#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got 5
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0) {
        return 0;
    }

    if (k >= pricesSize / 2) {
        long long max_profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                max_profit += (long long)prices[i] - (long long)prices[i - 1];
            }
        }
        return (int)max_profit;
    }

    long long* buy = (long long*)malloc(sizeof(long long) * (k + 1));
    long long* sell = (long long*)malloc(sizeof(long long) * (k + 1));

    for (int i = 0; i <= k; i++) {
        buy[i] = LLONG_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            if (sell[j - 1] - prices[i] > buy[j]) {
                buy[j] = sell[j - 1] - prices[i];
            }
            if (buy[j] != LLONG_MIN && buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] + prices[i];
            }
        }
    }

    int result = (int)sell[k];
    
    free(buy);
    free(sell);

    return result;
}

int main(void) {
    int k;
    if (scanf("%d", &k) == 1) {
        int capacity = 1000;
        int* prices = (int*)malloc(capacity * sizeof(int));
        if (!prices) return 1;

        int pricesSize = 0;
        int val;
        
        while (1) {
            int res = scanf("%d", &val);
            if (res == 1) {
                if (pricesSize >= capacity) {
                    capacity *= 2;
                    int* temp = (int*)realloc(prices, capacity * sizeof(int));
                    if (!temp) {
                        free(prices);
                        return 1;
                    }
                    prices = temp;
                }
                prices[pricesSize++] = val;
            } else {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                int c = getchar();
                if (c == EOF) break;
            }
        }
        
        printf("%d\n", maxProfit(k, prices, pricesSize));
        free(prices);
    }
    return 0;
}