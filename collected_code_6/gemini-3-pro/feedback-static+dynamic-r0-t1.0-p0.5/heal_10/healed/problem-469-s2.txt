#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_int(int *val) {
    int c;
    int sign = 1;
    while ((c = getchar()) != EOF && !isdigit(c) && c != '-');
    if (c == EOF) return 0;
    if (c == '-') {
        sign = -1;
        c = getchar();
        if (c == EOF || !isdigit(c)) {
            if (c != EOF) ungetc(c, stdin);
            return 0;
        }
    }
    *val = c - '0';
    while ((c = getchar()) != EOF && isdigit(c)) {
        *val = *val * 10 + (c - '0');
    }
    *val *= sign;
    if (c != EOF && !isdigit(c)) {
        ungetc(c, stdin);
    }
    return 1;
}

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize == 0 || k == 0) return 0;
    
    if (k >= pricesSize / 2) {
        int max_profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int *buy = (int *)malloc((k + 1) * sizeof(int));
    int *sell = (int *)malloc((k + 1) * sizeof(int));
    
    for (int i = 0; i <= k; i++) {
        buy[i] = -1000000000;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            if (buy[j] < sell[j - 1] - prices[i]) 
                buy[j] = sell[j - 1] - prices[i];
            if (sell[j] < buy[j] + prices[i]) 
                sell[j] = buy[j] + prices[i];
        }
    }
    
    int result = sell[k];
    free(buy);
    free(sell);
    
    return result;
}

int main() {
    int k, n;
    if (read_int(&k) && read_int(&n)) {
        int *prices = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            read_int(&prices[i]);
        }
        printf("%d\n", maxProfit(k, prices, n));
        free(prices);
    }
    return 0;
}