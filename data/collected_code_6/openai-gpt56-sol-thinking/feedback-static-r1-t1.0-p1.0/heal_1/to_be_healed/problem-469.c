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

static MaxProfitStatus max_profit(const int64_t *prices, size_t count,
                                  size_t max_transactions, int64_t *result)
{
    int64_t *cash = NULL;
    int64_t *hold = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'profit' can be reduced. [variableScope]
     */
    int64_t profit = 0;
    size_t i;
    size_t transaction;

    if (result == NULL || (count > 0 && prices == NULL)) {
        return MAX_PROFIT_INVALID_ARGUMENT;
    }

    *result = 0;

    for (i = 0; i < count; ++i) {
        if (prices[i] < 0) {
            return MAX_PROFIT_INVALID_ARGUMENT;
        }
    }

    if (count < 2 || max_transactions == 0) {
        return MAX_PROFIT_OK;
    }

    if (max_transactions >= count / 2) {
        for (i = 1; i < count; ++i) {
            if (prices[i] > prices[i - 1]) {
                int64_t gain = prices[i] - prices[i - 1];

                if (profit > INT64_MAX - gain) {
                    return MAX_PROFIT_OVERFLOW;
                }

                profit += gain;
            }
        }

        *result = profit;
        return MAX_PROFIT_OK;
    }

    if (max_transactions == SIZE_MAX ||
        max_transactions + 1 > SIZE_MAX / sizeof(*cash)) {
        return MAX_PROFIT_ALLOCATION_FAILURE;
    }

    cash = calloc(max_transactions + 1, sizeof(*cash));
    hold = malloc((max_transactions + 1) * sizeof(*hold));

    if (cash == NULL || hold == NULL) {
        free(hold);
        free(cash);
        return MAX_PROFIT_ALLOCATION_FAILURE;
    }

    for (transaction = 0; transaction <= max_transactions; ++transaction) {
        hold[transaction] = INT64_MIN;
    }

    for (i = 0; i < count; ++i) {
        for (transaction = 1; transaction <= max_transactions; ++transaction) {
            int64_t candidate_hold = cash[transaction - 1] - prices[i];
            int64_t candidate_cash;

            if (candidate_hold > hold[transaction]) {
                hold[transaction] = candidate_hold;
            }

            if (hold[transaction] > INT64_MAX - prices[i]) {
                free(hold);
                free(cash);
                return MAX_PROFIT_OVERFLOW;
            }

            candidate_cash = hold[transaction] + prices[i];

            if (candidate_cash > cash[transaction]) {
                cash[transaction] = candidate_cash;
            }
        }
    }

    *result = cash[max_transactions];

    free(hold);
    free(cash);

    return MAX_PROFIT_OK;
}

int main(void)
{
    const int64_t prices[] = {3, 2, 6, 5, 0, 3};
    const size_t count = sizeof(prices) / sizeof(prices[0]);
    const size_t max_transactions = 2;
    int64_t result;
    MaxProfitStatus status;

    status = max_profit(prices, count, max_transactions, &result);
    if (status != MAX_PROFIT_OK) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}