#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

typedef struct {
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool error;
} InputStream;

static int input_get(InputStream *input)
{
    if (input->position == input->length) {
        input->length = fread(input->buffer, 1, sizeof(input->buffer), stdin);
        input->position = 0;

        if (input->length == 0) {
            input->error = ferror(stdin) != 0;
            return EOF;
        }
    }

    return input->buffer[input->position++];
}

static bool read_uintmax_bounded(InputStream *input, uintmax_t limit,
                                 uintmax_t *result)
{
    uintmax_t value = 0;
    bool overflow = false;
    int c;

    if (input == NULL || result == NULL) {
        return false;
    }

    do {
        c = input_get(input);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    if (c == '+') {
        c = input_get(input);

        if (c == EOF) {
            return false;
        }
    }

    if (!isdigit((unsigned char)c)) {
        return false;
    }

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (!overflow) {
            if (value > limit / 10 ||
                (value == limit / 10 && digit > limit % 10)) {
                overflow = true;
            } else {
                value = value * 10 + digit;
            }
        }

        c = input_get(input);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (input->error || overflow) {
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
    int64_t *buy = NULL;
    int64_t *sell = NULL;

    if (result == NULL || (count != 0 && prices == NULL)) {
        return false;
    }

    *result = 0;

    if (count < 2 || max_transactions == 0) {
        return true;
    }

    if (max_transactions >= count / 2) {
        int64_t profit = 0;

        for (size_t i = 1; i < count; ++i) {
            if (prices[i] > prices[i - 1]) {
                int64_t gain;

                if (!checked_subtract_int64(prices[i], prices[i - 1],
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

    for (size_t transaction = 0;
         transaction < state_count;
         ++transaction) {
        buy[transaction] = INT64_MIN;
    }

    for (size_t day = 0; day < count; ++day) {
        for (size_t transaction = 1;
             transaction <= max_transactions;
             ++transaction) {
            int64_t buy_candidate;
            int64_t sell_candidate;

            if (!checked_subtract_int64(sell[transaction - 1],
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
    InputStream input = { { 0 }, 0, 0, false };
    uintmax_t count_input;
    uintmax_t transactions_input;
    int64_t *prices = NULL;
    int64_t profit;

    if (!read_uintmax_bounded(&input, SIZE_MAX, &count_input) ||
        !read_uintmax_bounded(&input, SIZE_MAX, &transactions_input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)count_input;
    size_t max_transactions = (size_t)transactions_input;

    if (count > SIZE_MAX / sizeof(*prices)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        prices = malloc(count * sizeof(*prices));

        if (prices == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        uintmax_t price_input;

        if (!read_uintmax_bounded(&input, INT64_MAX, &price_input)) {
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

    if (printf("%" PRId64 "\n", profit) < 0) {
        fputs("Output error\n", stderr);
        free(prices);
        return EXIT_FAILURE;
    }

    free(prices);
    return EXIT_SUCCESS;
}