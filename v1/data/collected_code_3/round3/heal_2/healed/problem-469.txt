#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProfit(int k, int n, int prices[]) {
    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++)
            if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
        return profit;
    }

    int *buy = malloc((k + 1) * sizeof(int));
    int *sell = malloc((k + 1) * sizeof(int));
   
    if(buy == NULL || sell == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i <= k; i++) buy[i] = INT_MIN;
    for (int i = 0; i <= k; i++) sell[i] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = k; j > 0; j--) {
            sell[j] = (sell[j] > buy[j] + prices[i]) ? sell[j] : buy[j] + prices[i];
            buy[j] = (buy[j] > (j > 1 ? sell[j - 1] : 0) - prices[i]) ? buy[j] : (j > 1 ? sell[j - 1] : 0) - prices[i];
        }
    }

    int maxProfit = sell[k];
    free(buy);
    free(sell);

    return maxProfit;
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    printf("Maximum profit earned: %d\n", maxProfit(k, n, prices));
    return 0;
}