#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  to match this '{'
 *  Unmatched '{'. Configuration: ''. [syntaxError]
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
    }

    /* Possible weaknesses found:
     *  expected '}'
     *  expected declaration or statement at end of input
     *  expected expression at end of input
     *  expected ';' at end of declaration
     *  expected expression
     */
    int* buy = (int*)malloc((k +