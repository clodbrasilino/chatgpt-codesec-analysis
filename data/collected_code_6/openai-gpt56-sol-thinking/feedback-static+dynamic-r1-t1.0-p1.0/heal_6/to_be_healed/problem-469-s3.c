#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

static bool read_uintmax_bounded(FILE *stream, uintmax_t limit,
                                 uintmax_t *result)
{
    uintmax_t value = 0;
    bool overflow = false;
    int c;

    if (stream == NULL || result == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    if (c == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);

        if (c == EOF) {
            return false;
        }
    }

    if (c < '0' || c > '9') {
        return false;
    }

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (!overflow) {
            if (value > limit / 10U ||
                (value == limit / 10U && digit > limit % 10U)) {
                overflow = true;
            } else {
                value = value * 10U + digit;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
    } while (c >= '0' && c <= '9');

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (ferror(stream) || overflow) {
        return false;
    }

    *result = value;
    return true;
}

static bool checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return false;
    }

    *result = left + right;
    return true;
}

static bool checked_subtract_int64(int64_t left, int64_t right,
                                   int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((right > 0 && left < INT64_MIN + right) ||
        (right < 0 && left > INT64_MAX + right)) {
        return false;
    }

    *result = left - right;
    return true;
}

static bool max_profit(const int64_t *prices, size_t count,
                       size_t max_transactions, int64_t *result)
{
    int64_t *buy;
    int64_t *sell;
    size_t state_count;

    if (result == NULL || (count != 0U && prices == NULL)) {
        return false;
    }

    *result = 0;

    if (count < 2U || max_transactions == 0U) {
        return true;
    }

    if (max_transactions >= count / 2U) {
        int64_t profit = 0;

        for (size_t day = 1U; day < count; ++day) {
            if (prices[day] > prices[day - 1U]) {
                int64_t gain;

                if (!checked_subtract_int64(prices[day],
                                            prices[day - 1U],
                                            &gain) ||
                    !checked_add_int64(profit, gain, &profit)) {
                    return false;
                }
            }
        }

        *result = profit;
        return true;
    }

    if (max_transactions == SIZE_MAX) {
        return false;
    }

    state_count = max_transactions + 1U;

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

    for (size_t transaction = 0U;
         transaction < state_count;
         ++transaction) {
        buy[transaction] = INT64_MIN;
    }

    for (size_t day = 0U; day < count; ++day) {
        for (size_t transaction = 1U;
             transaction <= max_transactions;
             ++transaction) {
            int64_t buy_candidate;
            int64_t sell_candidate;

            if (!checked_subtract_int64(sell[transaction - 1U],
                                        prices[day],
                                        &buy_candidate)) {
                free(buy);
                free(sell);
                return false;
            }

            if (buy_candidate > buy[transaction]) {
                buy[transaction] = buy_candidate;
            }

            if (!checked_add_int64(buy[transaction],
                                   prices[day],
                                   &sell_candidate)) {
                free(buy);
                free(sell);
                return false;
            }

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
    int64_t profit;
    size_t count;
    size_t max_transactions;

    if (!read_uintmax_bounded(stdin, SIZE_MAX, &count_input) ||
        !read_uintmax_bounded(stdin, SIZE_MAX, &transactions_input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)count_input;
    max_transactions = (size_t)transactions_input;

    if (count > SIZE_MAX / sizeof(*prices)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        prices = malloc(count * sizeof(*prices));

        if (prices == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0U; index < count; ++index) {
        uintmax_t price_input;

        if (!read_uintmax_bounded(stdin, (uintmax_t)INT64_MAX,
                                  &price_input)) {
            fputs("Invalid stock price\n", stderr);
            free(prices);
            return EXIT_FAILURE;
        }

        prices[index] = (int64_t)price_input;
    }

    if (!max_profit(prices, count, max_transactions, &profit)) {
        fputs("Unable to calculate profit\n", stderr);
        free(prices);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", profit) < 0 || fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        free(prices);
        return EXIT_FAILURE;
    }

    free(prices);
    return EXIT_SUCCESS;
}