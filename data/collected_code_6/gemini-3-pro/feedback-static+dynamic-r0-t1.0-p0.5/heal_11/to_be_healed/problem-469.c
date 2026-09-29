#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Possible weaknesses found:
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 *  to match this '{'
 */
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
    /* Possible weaknesses found:
     *  expected declaration or statement at end of input
     *  expected '}'
     */
    }