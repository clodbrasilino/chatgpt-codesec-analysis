#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool error;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    reader->stream = stream;
    reader->position = 0U;
    reader->length = 0U;
    reader->error = false;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->error) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1U,
                               sizeof(reader->buffer), reader->stream);
        reader->position = 0U;

        if (reader->length == 0U) {
            if (ferror(reader->stream) != 0) {
                reader->error = true;
            }

            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static bool read_uintmax_bounded(InputReader *reader, uintmax_t limit,
                                 uintmax_t *result)
{
    uintmax_t value = UINTMAX_C(0);
    uintmax_t quotient = limit / UINTMAX_C(10);
    uintmax_t remainder = limit % UINTMAX_C(10);
    bool overflow = false;
    int character;

    if (reader == NULL || result == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    if (character == EOF) {
        return false;
    }

    if (character == '+') {
        character = input_reader_get(reader);

        if (character == EOF) {
            return false;
        }
    }

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        unsigned int digit = (unsigned int)(character - '0');

        if (!overflow) {
            if (value > quotient ||
                (value == quotient && (uintmax_t)digit > remainder)) {
                overflow = true;
            } else {
                value = value * UINTMAX_C(10) + (uintmax_t)digit;
            }
        }

        character = input_reader_get(reader);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (reader->error) {
            return false;
        }
    } else if (isspace((unsigned char)character) == 0) {
        return false;
    }

    if (overflow) {
        return false;
    }

    *result = value;
    return true;
}

static bool input_at_end(InputReader *reader)
{
    int character;

    if (reader == NULL) {
        return false;
    }

    do {
        character = input_reader_get(reader);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    return character == EOF && !reader->error;
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

    *result = INT64_C(0);

    if (count < 2U || max_transactions == 0U) {
        return true;
    }

    if (max_transactions >= count / 2U) {
        int64_t profit = INT64_C(0);

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

    if (!input_at_end(&reader)) {
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