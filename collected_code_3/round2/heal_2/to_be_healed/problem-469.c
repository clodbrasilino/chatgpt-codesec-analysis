#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, int* prices, int pricesSize) {
    if(pricesSize == 0) return 0;
    if(k >= pricesSize / 2) {
        int res = 0;
        for(int i = 1; i < pricesSize; i++) {
            if(prices[i] > prices[i - 1]) res += prices[i] - prices[i - 1];
        }
        return res;
    }
    int** dp = (int**)malloc((k + 1) * sizeof(int*));
    if(dp == NULL) return -1;
    for(int i = 0; i <= k; i++) {
        dp[i] = (int*)malloc(pricesSize * sizeof(int));
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         *  leak of 'dp' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        if(dp[i] == NULL) return -1;
    }
    for(int i = 0; i <= k; i++)
        for(int j = 0; j < pricesSize; j++)
            dp[i][j] = 0;
    for(int i = 1; i <= k; i++) {
        int localMax = dp[i - 1][0] - prices[0];
        for(int j = 1; j < pricesSize; j++) {
            /* Possible weaknesses found:
             *  use of uninitialized value '*_56 + _59' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            dp[i][j] = dp[i][j - 1] > prices[j] + localMax ? dp[i][j - 1] : prices[j] + localMax;
            localMax = dp[i - 1][j] - prices[j] > localMax ? dp[i - 1][j] - prices[j] : localMax;
        }
    }
    /* Possible weaknesses found:
     *  use of uninitialized value '*dp_118 + _85' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    int result = dp[k][pricesSize - 1];
    for(int i = 0; i <= k; i++)
        free(dp[i]);
    free(dp);
    return result;
}

int main() {
    int prices[] = {3,2,6,5,0,3};
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int max_profit = maxProfit(k, prices, pricesSize);
    printf("Maximum profit is %d\n", max_profit);
    return 0;
}