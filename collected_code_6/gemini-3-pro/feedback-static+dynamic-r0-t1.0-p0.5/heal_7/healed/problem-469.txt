#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    while ((c = getchar()) != EOF && !isdigit(c) && c != '-') {}
    if (c == EOF) return 0;
    if (c == '-') {
        sign = -1;
        c = getchar();
        if (!isdigit(c)) return 0;
    }
    *val = 0;
    do {
        *val = *val * 10 + (c - '0');
    } while ((c = getchar()) != EOF && isdigit(c));
    *val *= sign;
    return 1;
}

int main(void) {
    int k;
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