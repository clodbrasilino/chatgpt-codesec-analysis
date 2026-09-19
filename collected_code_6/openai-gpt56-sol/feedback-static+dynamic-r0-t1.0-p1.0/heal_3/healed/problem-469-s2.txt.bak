#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

static bool add_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool subtract_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return false;
    }

    *result = a - b;
    return true;
}

static bool max_profit(const int64_t *prices, size_t count, size_t k,
                       int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    *result = 0;

    if (prices == NULL || count < 2U || k == 0U) {
        return true;
    }

    if (k >= count / 2U) {
        int64_t profit = 0;

        for (size_t i = 1U; i < count; ++i) {
            if (prices[i] > prices[i - 1U]) {
                int64_t difference;

                if (!subtract_int64(prices[i], prices[i - 1U], &difference) ||
                    !add_int64(profit, difference, &profit)) {
                    return false;
                }
            }
        }

        *result = profit;
        return true;
    }

    if (k == SIZE_MAX || k + 1U > SIZE_MAX / sizeof(int64_t)) {
        return false;
    }

    size_t elements = k + 1U;
    int64_t *previous = calloc(elements, sizeof(*previous));
    int64_t *current = calloc(elements, sizeof(*current));
    int64_t *best = malloc(elements * sizeof(*best));

    if (previous == NULL || current == NULL || best == NULL) {
        free(previous);
        free(current);
        free(best);
        return false;
    }

    best[0] = 0;

    for (size_t transaction = 1U; transaction <= k; ++transaction) {
        if (!subtract_int64(0, prices[0], &best[transaction])) {
            free(previous);
            free(current);
            free(best);
            return false;
        }
    }

    for (size_t day = 1U; day < count; ++day) {
        current[0] = 0;

        for (size_t transaction = 1U; transaction <= k; ++transaction) {
            int64_t candidate;
            int64_t sell_profit;

            if (!subtract_int64(previous[transaction - 1U], prices[day],
                                &candidate)) {
                free(previous);
                free(current);
                free(best);
                return false;
            }

            if (candidate > best[transaction]) {
                best[transaction] = candidate;
            }

            if (!add_int64(prices[day], best[transaction], &sell_profit)) {
                free(previous);
                free(current);
                free(best);
                return false;
            }

            current[transaction] =
                previous[transaction] > sell_profit
                    ? previous[transaction]
                    : sell_profit;
        }

        int64_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *result = previous[k];

    free(previous);
    free(current);
    free(best);
    return true;
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

    int64_t profit;

    if (!max_profit(prices, count, k, &profit)) {
        free(prices);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", profit) < 0) {
        free(prices);
        return EXIT_FAILURE;
    }

    free(prices);
    return EXIT_SUCCESS;
}