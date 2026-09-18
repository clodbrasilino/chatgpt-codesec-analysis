#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

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

    int* buy = (int*)malloc(sizeof(int) * (k + 1));
    int* sell = (int*)malloc(sizeof(int) * (k + 1));

    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            buy[j] = MAX(buy[j], sell[j - 1] - prices[i]);
            sell[j] = MAX(sell[j], buy[j] + prices[i]);
        }
    }

    int result = sell[k];
    
    free(buy);
    free(sell);

    return result;
}

int main(void) {
    int k = -1;
    int capacity = 1000;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (!prices) return 1;
    
    int pricesSize = 0;
    int sign = 1, val = 0, has_val = 0;
    int c;
    
    while ((c = getchar()) != EOF) {
        if (c == '-') {
            sign = -1;
        } else if (c >= '0' && c <= '9') {
            val = val * 10 + (c - '0');
            has_val = 1;
        } else {
            if (has_val) {
                if (k == -1) {
                    k = sign * val;
                } else {
                    if (pricesSize >= capacity) {
                        capacity *= 2;
                        int* temp = (int*)realloc(prices, capacity * sizeof(int));
                        if (!temp) {
                            free(prices);
                            return 1;
                        }
                        prices = temp;
                    }
                    prices[pricesSize++] = sign * val;
                }
                has_val = 0;
                val = 0;
                sign = 1;
            } else {
                sign = 1;
            }
        }
    }
    
    if (has_val) {
        if (k == -1) {
            k = sign * val;
        } else {
            if (pricesSize >= capacity) {
                capacity *= 2;
                int* temp = (int*)realloc(prices, capacity * sizeof(int));
                if (!temp) {
                    free(prices);
                    return 1;
                }
                prices = temp;
            }
            prices[pricesSize++] = sign * val;
        }
    }
    
    if (k != -1) {
        printf("%d\n", maxProfit(k, prices, pricesSize));
    }
    
    free(prices);
    return 0;
}