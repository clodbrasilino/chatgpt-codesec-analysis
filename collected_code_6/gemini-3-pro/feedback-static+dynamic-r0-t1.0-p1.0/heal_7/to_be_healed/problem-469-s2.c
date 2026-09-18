#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* Possible weaknesses found:
 *  to match this '{'
 */
int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0 || prices == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  to match this '{'
     */
    if (k >= pricesSize / 2) {
        int max_profit = 0;
        /* Possible weaknesses found:
         *  to match this '{'
         */
        for (int i = 1; i < pricesSize; i++) {
            /* Possible weaknesses found:
             *  to match this '{'
             *  Unmatched '{'. Configuration: ''. [syntaxError]
             */
            if (prices[i] > prices[i - 1]) {
                /* Possible weaknesses found:
                 *  expected ']'
                 *  expected ']' at end of input
                 *  to match this '['
                 *  expected declaration or statement at end of input
                 *  expected '}'
                 */
                max_profit += prices[i] - prices[i - 1