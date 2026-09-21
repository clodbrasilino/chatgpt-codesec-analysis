#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL(a, b) ((a) > (b) ? (a) : (b))
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

int max_profit(int k, const int* prices, int n) {
    if (n <= 1 || k <= 0 || prices == NULL) {
        return 0;
    }

    if (k >= n / 2) {
        int total_profit = 0;
        for (int i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                total_profit += prices[i] - prices[i - 1];
            }
        }
        return total_profit;
    }

    int* profit = (int*)calloc((size_t)n, sizeof(int));
    if (!profit) {
        return 0;
    }

    for (int t = 1; t <= k; ++t) {
        int max_diff = -prices[0];
        for (int i = 1; i < n; ++i) {
            int prev_profit = profit[i];
            profit[i] = MAX_VAL(profit[i - 1], prices[i] + max_diff);
            max_diff = MAX_VAL(max_diff, prev_profit - prices[i]);
        }
    }

    int result = profit[n - 1];
    free(profit);
    
    return result;
}

int main(void) {
    int k = 0;
    int has_k = 0;
    int n = 0;
    int cap = 16;
    int *prices = (int*)malloc((size_t)cap * sizeof(int));
    if (!prices) {
        return 0;
    }
    
    int c;
    int num = 0;
    int sign = 1;
    int in_num = 0;
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF) {
        if (c == '-') {
            sign = -1;
        } else if (c >= '0' && c <= '9') {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 777777777 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:2164,execs:255,op:havoc,rep:7)
             * UBSan: signed integer overflow: 666666666 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:2665,execs:313,op:havoc,rep:6)
             * UBSan: signed integer overflow: 555555555 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:5182,execs:610,op:havoc,rep:8)
             */
            num = num * 10 + (c - '0');
            in_num = 1;
        } else {
            if (in_num) {
                if (!has_k) {
                    k = num * sign;
                    has_k = 1;
                } else {
                    if (n >= cap) {
                        cap *= 2;
                        int *new_prices = (int*)realloc(prices, (size_t)cap * sizeof(int));
                        if (!new_prices) {
                            free(prices);
                            return 0;
                        }
                        prices = new_prices;
                    }
                    prices[n++] = num * sign;
                }
                num = 0;
                sign = 1;
                in_num = 0;
            } else {
                sign = 1;
            }
        }
    }
    
    if (in_num) {
        if (!has_k) {
            k = num * sign;
            has_k = 1;
        } else {
            if (n >= cap) {
                cap *= 2;
                int *new_prices = (int*)realloc(prices, (size_t)cap * sizeof(int));
                if (!new_prices) {
                    free(prices);
                    return 0;
                }
                prices = new_prices;
            }
            prices[n++] = num * sign;
        }
    }

    if (!has_k) {
        printf("0\n");
        free(prices);
        return 0;
    }

    int profit = max_profit(k, prices, n);
    printf("%d\n", profit);

    free(prices);
    return 0;
}