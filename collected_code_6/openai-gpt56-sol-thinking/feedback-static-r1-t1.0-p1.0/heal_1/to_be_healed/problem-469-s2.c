#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MAX_PROFIT_OK = 0,
    MAX_PROFIT_INVALID_ARGUMENT,
    MAX_PROFIT_ALLOCATION_FAILURE,
    MAX_PROFIT_OVERFLOW
} MaxProfitStatus;

MaxProfitStatus find_max_profit(const int64_t *prices,
                                size_t count,
                                size_t max_transactions,
                                int64_t *profit_out)
{
    int64_t *buy;
    int64_t *sell;
    /* Possible weaknesses found:
     *  The scope of the variable 'profit' can be reduced. [variableScope]
     */
    int64_t profit;
    size_t states;
    size_t i;
    size_t transaction;

    if (profit_out == NULL || (prices == NULL && count != 0U)) {
        return MAX_PROFIT_INVALID_ARGUMENT;
    }

    *profit_out = 0;

    for (i = 0; i < count; ++i) {
        if (prices[i] < 0) {
            return MAX_PROFIT_INVALID_ARGUMENT;
        }
    }

    if (count < 2U || max_transactions == 0U) {
        return MAX_PROFIT_OK;
    }

    if (max_transactions >= count / 2U) {
        profit = 0;

        for (i = 1; i < count; ++i) {
            if (prices[i] > prices[i - 1U]) {
                int64_t gain = prices[i] - prices[i - 1U];

                if (profit > INT64_MAX - gain) {
                    return MAX_PROFIT_OVERFLOW;
                }

                profit += gain;
            }
        }

        *profit_out = profit;
        return MAX_PROFIT_OK;
    }

    if (max_transactions == SIZE_MAX) {
        return MAX_PROFIT_ALLOCATION_FAILURE;
    }

    states = max_transactions + 1U;

    if (states > SIZE_MAX / sizeof(*buy)) {
        return MAX_PROFIT_ALLOCATION_FAILURE;
    }

    buy = malloc(states * sizeof(*buy));
    if (buy == NULL) {
        return MAX_PROFIT_ALLOCATION_FAILURE;
    }

    sell = malloc(states * sizeof(*sell));
    if (sell == NULL) {
        free(buy);
        return MAX_PROFIT_ALLOCATION_FAILURE;
    }

    buy[0] = 0;
    sell[0] = 0;

    for (transaction = 1; transaction <= max_transactions; ++transaction) {
        buy[transaction] = -prices[0];
        sell[transaction] = 0;
    }

    for (i = 1; i < count; ++i) {
        for (transaction = 1; transaction <= max_transactions; ++transaction) {
            int64_t candidate_buy = sell[transaction - 1U] - prices[i];
            int64_t candidate_sell;

            if (candidate_buy > buy[transaction]) {
                buy[transaction] = candidate_buy;
            }

            if (buy[transaction] > INT64_MAX - prices[i]) {
                free(sell);
                free(buy);
                return MAX_PROFIT_OVERFLOW;
            }

            candidate_sell = buy[transaction] + prices[i];

            if (candidate_sell > sell[transaction]) {
                sell[transaction] = candidate_sell;
            }
        }
    }

    *profit_out = sell[max_transactions];

    free(sell);
    free(buy);

    return MAX_PROFIT_OK;
}

int main(void)
{
    const int64_t prices[] = {3, 2, 6, 5, 0, 3};
    const size_t transaction_limit = 2U;
    const size_t price_count = sizeof(prices) / sizeof(prices[0]);
    int64_t profit;
    MaxProfitStatus status;

    status = find_max_profit(prices, price_count, transaction_limit, &profit);
    if (status != MAX_PROFIT_OK) {
        fprintf(stderr, "Unable to calculate maximum profit: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", profit);
    return EXIT_SUCCESS;
}