#include <stdio.h>
#include <stdlib.h>

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

    int* buy = (int*)malloc((k + 1) * sizeof(int));
    int* sell = (int*)malloc((k + 1) * sizeof(int));

    for (int i = 0; i <= k; i++) {
        buy[i] = -1000000000;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = k; j >= 1; j--) {
            if (buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] +