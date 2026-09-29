#include <stdio.h>
#include <stdlib.h>
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
        int max_profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int* dp = (int*)calloc(pricesSize, sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 1; i <= k; i++) {
        int max_diff = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            int prev_dp = dp[j];
            
            int curr_profit = prices[j] + max_diff;
            if (dp[j - 1] > curr_profit) {
                dp[j] = dp[j - 1];
            } else {
                dp[j] = curr_profit;
            }

            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1504774368 - -1939982109 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:47077,execs:13388,op:havoc,rep:2)
             * UBSan: signed integer overflow: 1294967299 - -1294967296 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000002,time:57430,execs:16324,op:havoc,rep:2)
             */
            int diff = prev_dp - prices[j];
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }

    int result = dp[pricesSize - 1];
    free(dp);

    return result;
}

int read_int(int *val) {
    int c;
    int sign = 1;
    long long temp = 0;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && !isdigit(c) && c != '-') {}
    if (c == EOF) return 0;
    if (c == '-') {
        sign = -1;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (!isdigit(c)) {
            return read_int(val);
        }
    }
    while (isdigit(c)) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5555555555555555555 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:47077,execs:13388,op:havoc,rep:2)
         * UBSan: signed integer overflow: 7777777777777777777 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:3839,execs:923,op:havoc,rep:1)
         */
        temp = temp * 10 + (c - '0');
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    }
    *val = (int)(temp * sign);
    return 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000002,time:48633,execs:13830,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int k = 0;
    if (!read_int(&k)) {
        return 0;
    }

    int capacity = 1000;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (!prices) {
        return 1;
    }
    
    int pricesSize = 0;
    int val;

    while (read_int(&val)) {
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
    }

    int profit = maxProfit(k, prices, pricesSize);
    printf("%d\n", profit);
    
    free(prices);
    return 0;
}