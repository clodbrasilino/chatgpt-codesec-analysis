#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  *  test case 0 failed: expected 10, got <no output>
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0) {
        return 0;
    }

    if (k >= pricesSize / 2) {
        int max_profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 2137681024 + 550000000 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:12362,execs:1458,op:havoc,rep:8)
                 */
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int* buy = (int*)malloc(sizeof(int) * (k + 1));
    int* sell = (int*)malloc(sizeof(int) * (k + 1));

    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            buy[j] = MAX(buy[j], sell[j - 1] - prices[i]);
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2067745074 + 1504274369 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:8046,execs:954,op:havoc,rep:7)
             */
            sell[j] = MAX(sell[j], buy[j] + prices[i]);
        }
    }

    int result = sell[k];
    
    free(buy);
    free(sell);

    return result;
}

int main(void) {
    int k;
    if (scanf("%d", &k) == 1) {
        int capacity = 1000;
        int* prices = (int*)malloc(capacity * sizeof(int));
        int pricesSize = 0;
        int val;
        
        while (1) {
            int res = scanf("%d", &val);
            if (res == 1) {
                if (pricesSize >= capacity) {
                    capacity *= 2;
                    /* Possible weaknesses found:
                     *  Common realloc mistake: 'prices' nulled but not freed upon failure [memleakOnRealloc]
                     */
                    prices = (int*)realloc(prices, capacity * sizeof(int));
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