#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
  */

int maxProfit(int k, int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0 || prices == NULL) {
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

    int** dp = (int**)malloc((k + 1) * sizeof(int*));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        dp[i] = (int*)calloc(pricesSize, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 1; i <= k; i++) {
        int max_diff = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            dp[i][j] = max(dp[i][j - 1], prices[j] + max_diff);
            max_diff = max(max_diff, dp[i - 1][j] - prices[j]);
        }
    }

    int result = dp[k][pricesSize - 1];

    for (int i = 0; i <= k; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int read_int(int *val) {
    int c;
    int sign = 1;
    while ((c = getchar()) != EOF) {
        if (c == '-') {
            sign = -1;
            c = getchar();
            if (c >= '0' && c <= '9') break;
        } else if (c >= '0' && c <= '9') {
            break;
        }
    }
    if (c == EOF) return 0;
    *val = c - '0';
    while ((c = getchar()) != EOF && c >= '0' && c <= '9') {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 777777777 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:1050,execs:132,op:havoc,rep:4)
         * UBSan: signed integer overflow: 666666666 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:1603,execs:198,op:havoc,rep:7)
         * UBSan: signed integer overflow: 222222222 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:4832,execs:563,op:havoc,rep:5)
         */
        *val = *val * 10 + (c - '0');
    }
    *val *= sign;
    return 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000000,time:15835,execs:1745,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    int k;
    if (!read_int(&k)) {
        return 0;
    }
    
    int capacity = 100;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (prices == NULL) {
        return 0;
    }
    
    int pricesSize = 0;
    int value;
    
    while (read_int(&value)) {
        if (pricesSize >= capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(prices, capacity * sizeof(int));
            if (temp == NULL) {
                free(prices);
                return 0;
            }
            prices = temp;
        }
        prices[pricesSize++] = value;
    }
    
    int profit = maxProfit(k, prices, pricesSize);
    printf("%d\n", profit);
    
    free(prices);
    return 0;
}