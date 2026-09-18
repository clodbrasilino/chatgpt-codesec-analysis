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
        int prev_dp_j_minus_1 = dp[0];
        for (int j = 1; j < pricesSize; j++) {
            int current_dp = dp[j];
            
            if (prev_dp_j_minus_1 - prices[j - 1] > max_diff) {
                max_diff = prev_dp_j_minus_1 - prices[j - 1];
            }
            
            int curr_profit = prices[j] + max_diff;
            prev_dp_j_minus_1 = current_dp;
            
            if (dp[j - 1] > curr_profit) {
                dp[j] = dp[j - 1];
            } else {
                dp[j] = curr_profit;
            }
        }
    }

    int result = dp[pricesSize - 1];
    free(dp);

    return result;
}

/* Possible weaknesses found:
 *  expected declaration specifiers or '...' at end of input
 *  expected ')'
 *  expected function body after function declarator
 *  expected parameter declarator
 *  to match this '('
 *  Unmatched '('. Configuration: ''. [syntaxError]
 */
int read_int(