#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maxProfit(long long k, const long long *prices, size_t pricesSize)
{
    if (prices == NULL || pricesSize < 2U || k <= 0LL) {
        return 0LL;
    }

    if ((unsigned long long)k >= (unsigned long long)(pricesSize / 2U)) {
        long long profit = 0LL;

        for (size_t i = 1U; i < pricesSize; ++i) {
            if (prices[i] > prices[i - 1U]) {
                profit += prices[i] - prices[i - 1U];
            }
        }

        return profit;
    }

    size_t t = (size_t)k;

    long long *buy = (long long *)malloc((t + 1U) * sizeof *buy);
    if (buy == NULL) {
        return 0LL;
    }

    long long *sell = (long long *)calloc(t + 1U, sizeof *sell);
    if (sell == NULL) {
        free(buy);
        return 0LL;
    }

    for (size_t j = 0U; j <= t; ++j) {
        buy[j] = LLONG_MIN;
    }

    for (size_t i = 0U; i < pricesSize; ++i) {
        for (size_t j = 1U; j <= t; ++j) {
            long long candidate = sell[j - 1U] - prices[i];

            if (buy[j] < candidate) {
                buy[j] = candidate;
            }

            if (buy[j] != LLONG_MIN) {
                long long value = buy[j] + prices[i];

                if (sell[j] < value) {
                    sell[j] = value;
                }
            }
        }
    }

    long long result = sell[t];

    free(sell);
    free(buy);

    return result;
}

int main(void)
{
    long long n;
    long long k;
    long long *prices = NULL;
    long long result;

    if (scanf("%lld", &n) != 1 || n < 0LL) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    if (scanf("%lld", &k) != 1 || k < 0LL) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    if (n > 0LL) {
        prices = (long long *)malloc((size_t)n * sizeof *prices);
        if (prices == NULL) {
            printf("0\n");
            return EXIT_SUCCESS;
        }

        for (long long i = 0LL; i < n; ++i) {
            if (scanf("%lld", &prices[i]) != 1) {
                free(prices);
                printf("0\n");
                return EXIT_SUCCESS;
            }
        }
    }

    result = maxProfit(k, prices, (size_t)n);
    printf("%lld\n", result);

    free(prices);

    return EXIT_SUCCESS;
}