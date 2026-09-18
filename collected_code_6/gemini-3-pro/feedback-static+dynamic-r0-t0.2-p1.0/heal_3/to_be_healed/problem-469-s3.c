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
     *  use of undeclared identifier 'call'
     *  expected declaration or statement at end of input
     *  expected ';' at end of declaration
     *  'call' undeclared (first use in this function); did you mean 'calloc'?
     *  each undeclared identifier is reported only once for each function it appears in
     *  expected ',' or ';' at end of input
     */
    int* dp = (int*)call