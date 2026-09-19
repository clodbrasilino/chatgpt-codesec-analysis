#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

static int64_t checked_add(int64_t a, int64_t b)
{
    if (b > 0 && a > INT64_MAX - b) {
        return INT64_MAX;
    }

    if (b < 0 && a < INT64_MIN - b) {
        return INT64_MIN;
    }

    return a + b;
}

static int64_t nonnegative_difference(int64_t high, int64_t low)
{
    if (high <= low) {
        return 0;
    }

    if (low < 0 && high > INT64_MAX + low) {
        return INT64_MAX;
    }

    return high - low;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got <no output>
  *  test case 0 failed: expected 10, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

static int64_t max_profit(const int64_t *prices, size_t count, size_t k)
{
    if (prices == NULL || count < 2U || k == 0U) {
        return 0;
    }

    if (k >= count / 2U) {
        int64_t profit = 0;

        for (size_t i = 1U; i < count; ++i) {
            profit = checked_add(
                profit,
                nonnegative_difference(prices[i], prices[i - 1U])
            );
        }

        return profit;
    }

    if (k > (SIZE_MAX / sizeof(int64_t)) - 1U) {
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
        best_buy[transaction] = -prices[0];
    }

    for (size_t day = 1U; day < count; ++day) {
        for (size_t transaction = 1U; transaction <= k; ++transaction) {
            int64_t buy_candidate =
                profit[transaction - 1U] >= prices[day]
                    ? profit[transaction - 1U] - prices[day]
                    : -prices[day] + profit[transaction - 1U];

            if (buy_candidate > best_buy[transaction]) {
                best_buy[transaction] = buy_candidate;
            }

            int64_t sell_candidate =
                checked_add(prices[day], best_buy[transaction]);

            if (sell_candidate > profit[transaction]) {
                profit[transaction] = sell_candidate;
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

    if (scanf("%zu %zu", &count, &k) != 2 || count == 0U) {
        return EXIT_FAILURE;
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

    int64_t profit = max_profit(prices, count, k);

    printf("%" PRId64 "\n", profit);

    free(prices);
    return EXIT_SUCCESS;
}