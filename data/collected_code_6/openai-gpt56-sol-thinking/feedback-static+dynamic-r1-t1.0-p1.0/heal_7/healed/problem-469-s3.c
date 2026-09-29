#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

typedef struct {
    FILE *stream;
    bool error;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader != NULL) {
        reader->stream = stream;
        reader->error = false;
    }
}

static int input_reader_get(InputReader *reader)
{
    int value;

    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    value = fgetc(reader->stream);

    if (value == EOF && ferror(reader->stream)) {
        reader->error = true;
    }

    return value;
}

static bool read_uintmax_bounded(InputReader *reader, uintmax_t limit,
                                 uintmax_t *result)
{
    uintmax_t value = 0U;
    bool overflow = false;
    int c;

    if (reader == NULL || reader->stream == NULL || result == NULL) {
        return false;
    }

    do {
        c = input_reader_get(reader);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    if (c == '+') {
        c = input_reader_get(reader);

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
            if (value > limit / UINTMAX_C(10) ||
                (value == limit / UINTMAX_C(10) &&
                 (uintmax_t)digit > limit % UINTMAX_C(10))) {
                overflow = true;
            } else {
                value = value * UINTMAX_C(10) + (uintmax_t)digit;
            }
        }

        c = input_reader_get(reader);
    } while (c >= '0' && c <= '9');

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (reader->error || overflow) {
        return false;
    }

    *result = value;
    return true;
}

static bool input_reader_at_end(InputReader *reader)
{
    int c;

    if (reader == NULL || reader->stream == NULL) {
        return false;
    }

    do {
        c = input_reader_get(reader);
    } while (c != EOF && isspace((unsigned char)c));

    return c == EOF && !reader->error;
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
    int64_t *buy = NULL;
    int64_t *sell = NULL;
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
        for (size_t transaction = max_transactions;
             transaction > 0U;
             --transaction) {
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
    InputReader reader;
    uintmax_t count_input;
    uintmax_t transactions_input;
    int64_t *prices = NULL;
    int64_t profit;
    size_t count;
    size_t max_transactions;

    input_reader_init(&reader, stdin);

    if (!read_uintmax_bounded(&reader, (uintmax_t)SIZE_MAX, &count_input) ||
        !read_uintmax_bounded(&reader, (uintmax_t)SIZE_MAX,
                              &transactions_input)) {
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

        if (!read_uintmax_bounded(&reader, (uintmax_t)INT64_MAX,
                                  &price_input)) {
            fputs("Invalid stock price\n", stderr);
            free(prices);
            return EXIT_FAILURE;
        }

        prices[index] = (int64_t)price_input;
    }

    if (!input_reader_at_end(&reader)) {
        fputs("Unexpected trailing input\n", stderr);
        free(prices);
        return EXIT_FAILURE;
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