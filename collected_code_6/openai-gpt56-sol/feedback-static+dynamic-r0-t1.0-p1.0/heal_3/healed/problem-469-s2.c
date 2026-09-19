#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>

static int64_t saturating_add(int64_t a, int64_t b)
{
    if (b > 0 && a > INT64_MAX - b) {
        return INT64_MAX;
    }

    if (b < 0 && a < INT64_MIN - b) {
        return INT64_MIN;
    }

    return a + b;
}

static int64_t saturating_subtract(int64_t a, int64_t b)
{
    if (b > 0 && a < INT64_MIN + b) {
        return INT64_MIN;
    }

    if (b < 0 && a > INT64_MAX + b) {
        return INT64_MAX;
    }

    return a - b;
}

static int64_t max_profit(const int64_t *prices, size_t count, size_t k)
{
    if (prices == NULL || count < 2U || k == 0U) {
        return 0;
    }

    if (k >= count / 2U) {
        int64_t result = 0;

        for (size_t i = 1U; i < count; ++i) {
            if (prices[i] > prices[i - 1U]) {
                result = saturating_add(
                    result,
                    saturating_subtract(prices[i], prices[i - 1U])
                );
            }
        }

        return result;
    }

    if (k == SIZE_MAX || k + 1U > SIZE_MAX / sizeof(int64_t)) {
        return 0;
    }

    int64_t *profit = calloc(k + 1U, sizeof(*profit));
    int64_t *best_buy = malloc((k + 1U) * sizeof(*best_buy));

    if (profit == NULL || best_buy == NULL) {
        free(profit);
        free(best_buy);
        return 0;
    }

    best_buy[0] = INT64_MIN;

    for (size_t transaction = 1U; transaction <= k; ++transaction) {
        best_buy[transaction] = saturating_subtract(0, prices[0]);
    }

    for (size_t day = 1U; day < count; ++day) {
        for (size_t transaction = k; transaction > 0U; --transaction) {
            int64_t sell_candidate =
                saturating_add(prices[day], best_buy[transaction]);

            if (sell_candidate > profit[transaction]) {
                profit[transaction] = sell_candidate;
            }

            int64_t buy_candidate =
                saturating_subtract(profit[transaction - 1U], prices[day]);

            if (buy_candidate > best_buy[transaction]) {
                best_buy[transaction] = buy_candidate;
            }
        }
    }

    int64_t result = profit[k];

    free(profit);
    free(best_buy);

    return result;
}

int main(void)
{
    size_t count;
    size_t k;

    if (scanf("%zu %zu", &count, &k) != 2) {
        return EXIT_FAILURE;
    }

    if (count == 0U) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *prices = malloc(count * sizeof(*prices));

    if (prices == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%" SCNd64, &prices[i]) != 1 || prices[i] < 0) {
            free(prices);
            return EXIT_FAILURE;
        }
    }

    int64_t result = max_profit(prices, count, k);

    free(prices);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}