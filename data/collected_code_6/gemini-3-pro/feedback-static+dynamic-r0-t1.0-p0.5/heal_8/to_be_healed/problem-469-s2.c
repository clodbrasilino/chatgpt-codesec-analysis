#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_int(int *val) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && !isdigit(c));
    if (c == EOF) return 0;
    long long temp = c - '0';
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && isdigit(c)) {
        temp = temp * 10 + (c - '0');
        if (temp > 2147483647) {
            temp = 2147483647;
        }
    }
    *val = (int)temp;
    return 1;
}
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
        int max_profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 888888000 + 2147482759 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000023,time:52616,execs:15515,op:havoc,rep:6)
                 * UBSan: signed integer overflow: 2147483643 + 200000000 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:30427,execs:8978,op:havoc,rep:5)
                 */
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int* buy = (int*)malloc((k + 1) * sizeof(int));
    int* sell = (int*)malloc((k + 1) * sizeof(int));

    if (!buy || !sell) {
        if (buy) free(buy);
        if (sell) free(sell);
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            int current_buy = sell[j - 1] - prices[i];
            if (buy[j] < current_buy) {
                buy[j] = current_buy;
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 48 + 2147483647 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:10175,execs:3090,op:havoc,rep:6)
             */
            int current_sell = buy[j] + prices[i];
            if (sell[j] < current_sell) {
                sell[j] = current_sell;
            }
        }
    }

    int result = sell[k];

    free(buy);
    free(sell);

    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:2352,execs:731,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    int k;
    if (!read_int(&k)) {
        return 0;
    }

    int capacity = 1000;
    int pricesSize = 0;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (!prices) {
        return 0;
    }

    int temp;
    while (read_int(&temp)) {
        prices[pricesSize++] = temp;
        if (pricesSize >= capacity) {
            capacity *= 2;
            int *new_prices = (int*)realloc(prices, capacity * sizeof(int));
            if (!new_prices) {
                free(prices);
                return 0;
            }
            prices = new_prices;
        }
    }

    printf("%d\n", maxProfit(k, prices, pricesSize));

    free(prices);
    return 0;
}