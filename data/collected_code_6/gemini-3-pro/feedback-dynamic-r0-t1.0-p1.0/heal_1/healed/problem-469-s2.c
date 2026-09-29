#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

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

int main() {
    int k;
    if (scanf("%d", &k) != 1) {
        return 0;
    }
    
    int capacity = 100;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (prices == NULL) {
        return 0;
    }
    
    int pricesSize = 0;
    int value;
    
    while (scanf("%d", &value) == 1) {
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