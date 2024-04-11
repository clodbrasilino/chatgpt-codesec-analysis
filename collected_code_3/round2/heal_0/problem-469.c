#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, int* prices, int pricesSize){
    if(pricesSize == 0) return 0;
    if(k >= pricesSize / 2) {
        int res = 0;
        for(int i = 1; i < pricesSize; i++) {
            if(prices[i] > prices[i - 1]) res += prices[i] - prices[i - 1];
        }
        return res;
    }
    int** dp = (int**)malloc((k + 1) * sizeof(int*));
    for(int i = 0; i <= k; i++) {
        dp[i] = (int*)malloc(pricesSize * sizeof(int));
    }
    for(int i = 1; i <= k; i++) {
        int localMax = dp[i - 1][0] - prices[0];
        for(int j = 1; j < pricesSize; j++) {
            dp[i][j] = dp[i][j - 1] > prices[j] + localMax ? dp[i][j - 1] : prices[j] + localMax;
            localMax = dp[i - 1][j] - prices[j] > localMax ? dp[i - 1][j] - prices[j] : localMax;
        }
    }
    return dp[k][pricesSize - 1];
}

int main() {
    int prices[] = {3,2,6,5,0,3};
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int max_profit = maxProfit(k, prices, pricesSize);
    printf("Maximum profit is %d\n", max_profit);
    return 0;
}