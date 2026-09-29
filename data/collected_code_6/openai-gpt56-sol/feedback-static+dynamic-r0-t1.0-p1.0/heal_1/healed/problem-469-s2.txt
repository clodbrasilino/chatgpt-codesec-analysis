#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>

static int checked_add(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int64_t max_profit(const int64_t *prices, size_t count, size_t k)
{
    if (prices == NULL || count < 2U || k == 0U) {
        return 0;
    }

    if (k >= count / 2U) {
        int64_t profit = 0;

        for (size_t i = 1U; i < count; ++i) {
            if (prices[i] > prices[i - 1U]) {
                int64_t gain = prices[i] - prices[i - 1U];

                if (!checked_add(profit, gain, &profit)) {
                    return INT64_MAX;
                }
            }
        }

        return profit;
    }

    if (k == SIZE_MAX || k + 1U > SIZE_MAX / sizeof(int64_t)) {
        return 0;
    }

    int64_t *previous = calloc(k + 1U, sizeof(*previous));
    int64_t *current = calloc(k + 1U, sizeof(*current));
    int64_t *best_difference = malloc((k + 1U) * sizeof(*best_difference));

    if (previous == NULL || current == NULL || best_difference == NULL) {
        free(previous);
        free(current);
        free(best_difference);
        return 0;
    }

    best_difference[0] = 0;

    for (size_t transaction = 1U; transaction <= k; ++transaction) {
        best_difference[transaction] = -prices[0];
    }

    for (size_t day = 1U; day < count; ++day) {
        current[0] = 0;

        for (size_t transaction = 1U; transaction <= k; ++transaction) {
            int64_t sell_profit;

            if (!checked_add(prices[day],
                             best_difference[transaction],
                             &sell_profit)) {
                sell_profit = INT64_MAX;
            }

            current[transaction] =
                previous[transaction] > sell_profit
                    ? previous[transaction]
                    : sell_profit;

            int64_t candidate =
                previous[transaction - 1U] - prices[day];

            if (candidate > best_difference[transaction]) {
                best_difference[transaction] = candidate;
            }
        }

        int64_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    int64_t result = previous[k];

    free(previous);
    free(current);
    free(best_difference);

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

    if (printf("%" PRId64 "\n", profit) < 0) {
        free(prices);
        return EXIT_FAILURE;
    }

    free(prices);
    return EXIT_SUCCESS;
}