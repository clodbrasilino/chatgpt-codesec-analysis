#include <stdio.h>

int maxProfit(int prices[], int n, int k) {
    int profit[k + 1][n + 1];

    for (int i = 0; i <= k; i++) {
        profit[i][0] = 0;
    }

    for (int j = 0; j <= n; j++) {
        profit[0][j] = 0;
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j < n; j++) {
            int maxProfit = 0;

            for (int m = 0; m < j; m++) {
                int temp = prices[j] - prices[m] + profit[i - 1][m];
                
                if (temp > maxProfit) {
                    maxProfit = temp;
                }
            }

            profit[i][j] = maxProfit > profit[i][j - 1] ? maxProfit : profit[i][j - 1];
        }
    }

    return profit[k][n - 1];
}

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;

    int max_profit = maxProfit(prices, n, k);
    printf("Maximum profit: %d\n", max_profit);

    return 0;
}