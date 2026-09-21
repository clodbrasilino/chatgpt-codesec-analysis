#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

static bool read_uintmax_limited(FILE *stream, uintmax_t limit, uintmax_t *value)
{
    int ch;
    uintmax_t parsed = 0;

    if (stream == NULL || value == NULL) {
        return false;
    }

    do {
        ch = fgetc(stream);
        if (ch == EOF) {
            return false;
        }
    } while (isspace((unsigned char)ch));

    if (ch == '+') {
        ch = fgetc(stream);
    }

    if (ch < '0' || ch > '9') {
        return false;
    }

    do {
        uintmax_t digit = (uintmax_t)(ch - '0');

        if (digit > limit || parsed > (limit - digit) / 10) {
            return false;
        }

        parsed = parsed * 10 + digit;
        ch = fgetc(stream);
    } while (ch >= '0' && ch <= '9');

    if (ch == EOF) {
        if (ferror(stream)) {
            return false;
        }
    } else if (!isspace((unsigned char)ch)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool max_profit(const int64_t *prices, size_t count,
                       size_t max_transactions, int64_t *result)
{
    int64_t *buy = NULL;
    int64_t *sell = NULL;

    if (result == NULL || (count > 0 && prices == NULL)) {
        return false;
    }

    *result = 0;

    for (size_t i = 0; i < count; ++i) {
        if (prices[i] < 0) {
            return false;
        }
    }

    if (count < 2 || max_transactions == 0) {
        return true;
    }

    if (max_transactions >= count / 2) {
        int64_t profit = 0;

        for (size_t i = 1; i < count; ++i) {
            if (prices[i] > prices[i - 1]) {
                int64_t gain = prices[i] - prices[i - 1];

                if (profit > INT64_MAX - gain) {
                    return false;
                }

                profit += gain;
            }
        }

        *result = profit;
        return true;
    }

    if (max_transactions == SIZE_MAX) {
        return false;
    }

    size_t state_count = max_transactions + 1;

    if (state_count > SIZE_MAX / sizeof(*buy)) {
        return false;
    }

    buy = malloc(state_count * sizeof(*buy));
    sell = calloc(state_count, sizeof(*sell));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return false;
    }

    for (size_t transaction = 0; transaction < state_count; ++transaction) {
        buy[transaction] = INT64_MIN;
    }

    for (size_t day = 0; day < count; ++day) {
        for (size_t transaction = 1;
             transaction <= max_transactions;
             ++transaction) {
            int64_t buy_candidate = sell[transaction - 1] - prices[day];

            if (buy_candidate > buy[transaction]) {
                buy[transaction] = buy_candidate;
            }

            if (buy[transaction] > INT64_MAX - prices[day]) {
                free(buy);
                free(sell);
                return false;
            }

            int64_t sell_candidate = buy[transaction] + prices[day];

            if (sell_candidate > sell[transaction]) {
                sell[transaction] = sell_candidate;
            }
        }
    }

    *result = sell[max_transactions];

    free(buy);
    free(sell);
    return true;
}

int main(void)
{
    uintmax_t count_input;
    uintmax_t transactions_input;
    int64_t *prices = NULL;
    int64_t profit = 0;

    if (!read_uintmax_limited(stdin, UINTMAX_MAX, &count_input) ||
        !read_uintmax_limited(stdin, UINTMAX_MAX, &transactions_input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_input > SIZE_MAX || transactions_input > SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)count_input;
    size_t max_transactions = (size_t)transactions_input;

    if (count > SIZE_MAX / sizeof(*prices)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        prices = malloc(count * sizeof(*prices));

        if (prices == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        uintmax_t price_input;

        if (!read_uintmax_limited(stdin, (uintmax_t)INT64_MAX, &price_input)) {
            fputs("Invalid stock price\n", stderr);
            free(prices);
            return EXIT_FAILURE;
        }

        prices[i] = (int64_t)price_input;
    }

    if (!max_profit(prices, count, max_transactions, &profit)) {
        fputs("Unable to calculate profit\n", stderr);
        free(prices);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", profit);

    free(prices);
    return EXIT_SUCCESS;
}