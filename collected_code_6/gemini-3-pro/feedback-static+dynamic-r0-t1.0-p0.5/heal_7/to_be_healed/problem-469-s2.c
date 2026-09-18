#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_int(int *val) {
    int c;
    while ((c = getchar()) != EOF && !isdigit(c));
    if (c == EOF) return 0;
    *val = c - '0';
    while ((c = getchar()) != EOF && isdigit(c)) {
        *val = *val * 10 + (c - '0');
    }
    return 1;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 7, got <no output>
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

    int* buy = (int*)malloc((k + 1) * sizeof(int));
    int* sell = (int*)malloc((k + 1) * sizeof(int));

    if (!buy || !sell) {
        if (buy) free(buy);
        if (sell) free(sell);
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            int current_buy = sell[j - 1] - prices[i];
            if (buy[j] < current_buy) {
                buy[j] = current_buy;
            }
            int current_sell = buy[j] + prices[i];
            if (sell[j] < current_sell) {
                sell[j] = current_sell;
            }
        }
    }

    int result = sell[k];

    free(buy);
    free(sell);

    return result;
}

int main(void) {
    int k;
    if (!read_int(&k)) {
        return 0;
    }

    int capacity = 1000;
    int pricesSize = 0;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (!prices) {
        return 0;
    }

    int temp;
    while (read_int(&temp)) {
        prices[pricesSize++] = temp;
        if (pricesSize >= capacity) {
            capacity *= 2;
            int *new_prices = (int*)realloc(prices, capacity * sizeof(int));
            if (!new_prices) {
                free(prices);
                return 0;
            }
            prices = new_prices;
        }
    }

    printf("%d\n", maxProfit(k, prices, pricesSize));

    free(prices);
    return 0;
}