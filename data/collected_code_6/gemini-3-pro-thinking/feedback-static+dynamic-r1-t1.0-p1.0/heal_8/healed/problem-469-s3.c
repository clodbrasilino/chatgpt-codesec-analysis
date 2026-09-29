#include <stdio.h>
#include <stdlib.h>

int max_profit(int k, const int* prices, int n) {
    if (n <= 1 || k <= 0 || prices == NULL) {
        return 0;
    }

    if (k >= n / 2) {
        long long total_profit = 0;
        for (int i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                total_profit += (long long)prices[i] - prices[i - 1];
            }
        }
        return (int)total_profit;
    }

    int* profit = (int*)calloc((size_t)n, sizeof(int));
    if (!profit) {
        return 0;
    }

    for (int t = 1; t <= k; ++t) {
        long long max_diff = -(long long)prices[0];
        for (int i = 1; i < n; ++i) {
            long long prev_profit = profit[i];
            long long current_profit = (long long)prices[i] + max_diff;
            if (current_profit > profit[i - 1]) {
                profit[i] = (int)current_profit;
            } else {
                profit[i] = profit[i - 1];
            }
            long long diff = prev_profit - prices[i];
            if (diff > max_diff) {
                max_diff = diff;
            }
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
    long long num = 0;
    int sign = 1;
    int in_num = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == '-') {
            sign = -1;
        } else if (c >= '0' && c <= '9') {
            if (num < 2147483648LL) {
                num = num * 10 + (c - '0');
            }
            in_num = 1;
        } else {
            if (in_num) {
                long long val = num * sign;
                if (val > 2147483647LL) val = 2147483647LL;
                if (val < -2147483648LL) val = -2147483648LL;
                int int_val = (int)val;
                
                if (!has_k) {
                    k = int_val;
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
                    prices[n++] = int_val;
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
        long long val = num * sign;
        if (val > 2147483647LL) val = 2147483647LL;
        if (val < -2147483648LL) val = -2147483648LL;
        int int_val = (int)val;

        if (!has_k) {
            k = int_val;
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
            prices[n++] = int_val;
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