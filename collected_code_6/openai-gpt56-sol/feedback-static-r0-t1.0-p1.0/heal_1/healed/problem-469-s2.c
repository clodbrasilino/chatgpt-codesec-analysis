#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int subtract_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return 0;
    }

    *result = a - b;
    return 1;
}

static int read_size_value(size_t *value)
{
    char input[128];
    char *end = NULL;
    uintmax_t parsed;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_price(int64_t *value)
{
    char input[128];
    char *end = NULL;
    intmax_t parsed;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed < 0 || parsed > INT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int max_profit(const int64_t *prices, size_t count, size_t k,
                      int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    *result = 0;

    if (prices == NULL || count < 2U || k == 0U) {
        return 1;
    }

    if (k >= count / 2U) {
        int64_t profit = 0;

        for (size_t i = 1U; i < count; ++i) {
            if (prices[i] > prices[i - 1U]) {
                int64_t difference;

                if (!subtract_int64(prices[i], prices[i - 1U], &difference) ||
                    !add_int64(profit, difference, &profit)) {
                    return 0;
                }
            }
        }

        *result = profit;
        return 1;
    }

    if (k == SIZE_MAX || k + 1U > SIZE_MAX / sizeof(int64_t)) {
        return 0;
    }

    int64_t *previous = calloc(k + 1U, sizeof(*previous));
    int64_t *current = calloc(k + 1U, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return 0;
    }

    for (size_t day = 1U; day < count; ++day) {
        int64_t best_difference = -prices[0];
        current[0] = 0;

        for (size_t transaction = 1U; transaction <= k; ++transaction) {
            int64_t sell_profit;
            int64_t candidate;

            if (!add_int64(prices[day], best_difference, &sell_profit) ||
                !subtract_int64(previous[transaction - 1U],
                                prices[day], &candidate)) {
                free(previous);
                free(current);
                return 0;
            }

            current[transaction] =
                previous[transaction] > sell_profit
                    ? previous[transaction]
                    : sell_profit;

            if (candidate > best_difference) {
                best_difference = candidate;
            }
        }

        int64_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *result = previous[k];

    free(previous);
    free(current);
    return 1;
}

int main(void)
{
    size_t count;
    size_t k;

    if (!read_size_value(&count) || count == 0U || !read_size_value(&k)) {
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
        if (!read_price(&prices[i])) {
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