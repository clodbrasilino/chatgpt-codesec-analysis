#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

typedef struct {
    FILE *stream;
    bool ended;
    bool failed;
} InputReader;

static bool input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->ended = false;
    reader->failed = false;

    return true;
}

static int input_reader_get(InputReader *reader, unsigned char *character)
{
    int input;

    if (reader == NULL || reader->stream == NULL || character == NULL) {
        return -1;
    }

    if (reader->ended) {
        return reader->failed ? -1 : 0;
    }

    input = fgetc(reader->stream);

    if (input != EOF) {
        *character = (unsigned char)input;
        return 1;
    }

    reader->ended = true;

    if (ferror(reader->stream) != 0 || feof(reader->stream) == 0) {
        reader->failed = true;
        return -1;
    }

    return 0;
}

static bool input_reader_finish(InputReader *reader)
{
    unsigned char character;

    if (reader == NULL) {
        return false;
    }

    for (;;) {
        int status = input_reader_get(reader, &character);

        if (status == 0) {
            return true;
        }

        if (status < 0 || isspace((int)character) == 0) {
            return false;
        }
    }
}

static bool read_uintmax_limited(InputReader *reader, uintmax_t limit,
                                 uintmax_t *value)
{
    unsigned char character;
    uintmax_t parsed = 0;
    int status;

    if (reader == NULL || value == NULL) {
        return false;
    }

    do {
        status = input_reader_get(reader, &character);

        if (status != 1) {
            return false;
        }
    } while (isspace((int)character) != 0);

    if (character == (unsigned char)'+') {
        status = input_reader_get(reader, &character);

        if (status != 1) {
            return false;
        }
    }

    if (character < (unsigned char)'0' ||
        character > (unsigned char)'9') {
        return false;
    }

    for (;;) {
        uintmax_t digit =
            (uintmax_t)(character - (unsigned char)'0');

        if (digit > limit ||
            parsed > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        parsed = parsed * UINTMAX_C(10) + digit;

        status = input_reader_get(reader, &character);

        if (status == 0) {
            *value = parsed;
            return true;
        }

        if (status < 0) {
            return false;
        }

        if (character < (unsigned char)'0' ||
            character > (unsigned char)'9') {
            break;
        }
    }

    if (isspace((int)character) == 0) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool add_int64_checked(int64_t left, int64_t right, int64_t *result)
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

static bool subtract_int64_checked(int64_t left, int64_t right,
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
    bool success = false;

    if (result == NULL || (count != 0 && prices == NULL)) {
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
                int64_t gain;

                if (!subtract_int64_checked(prices[i], prices[i - 1],
                                            &gain) ||
                    !add_int64_checked(profit, gain, &profit)) {
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

    state_count = max_transactions + 1;

    if (state_count > SIZE_MAX / sizeof(*buy) ||
        state_count > SIZE_MAX / sizeof(*sell)) {
        return false;
    }

    buy = malloc(state_count * sizeof(*buy));
    sell = calloc(state_count, sizeof(*sell));

    if (buy == NULL || sell == NULL) {
        goto cleanup;
    }

    for (size_t transaction = 0;
         transaction < state_count;
         ++transaction) {
        buy[transaction] = INT64_MIN;
    }

    for (size_t day = 0; day < count; ++day) {
        for (size_t transaction = max_transactions;
             transaction > 0;
             --transaction) {
            int64_t buy_candidate;
            int64_t sell_candidate;

            if (!subtract_int64_checked(sell[transaction - 1],
                                        prices[day],
                                        &buy_candidate)) {
                goto cleanup;
            }

            if (buy_candidate > buy[transaction]) {
                buy[transaction] = buy_candidate;
            }

            if (!add_int64_checked(buy[transaction], prices[day],
                                   &sell_candidate)) {
                goto cleanup;
            }

            if (sell_candidate > sell[transaction]) {
                sell[transaction] = sell_candidate;
            }
        }
    }

    *result = sell[max_transactions];
    success = true;

cleanup:
    free(buy);
    free(sell);
    return success;
}

int main(void)
{
    InputReader reader;
    uintmax_t count_input;
    uintmax_t transactions_input;
    int64_t *prices = NULL;
    int64_t profit = 0;
    int exit_status = EXIT_FAILURE;

    if (!input_reader_init(&reader, stdin)) {
        fputs("Unable to initialize input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_uintmax_limited(&reader, UINTMAX_MAX, &count_input) ||
        !read_uintmax_limited(&reader, UINTMAX_MAX,
                              &transactions_input)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (count_input > (uintmax_t)SIZE_MAX ||
        transactions_input > (uintmax_t)SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        goto cleanup;
    }

    {
        size_t count = (size_t)count_input;
        size_t max_transactions = (size_t)transactions_input;

        if (count > SIZE_MAX / sizeof(*prices)) {
            fputs("Input is too large\n", stderr);
            goto cleanup;
        }

        if (count != 0) {
            prices = malloc(count * sizeof(*prices));

            if (prices == NULL) {
                fputs("Memory allocation failed\n", stderr);
                goto cleanup;
            }
        }

        for (size_t i = 0; i < count; ++i) {
            uintmax_t price_input;

            if (!read_uintmax_limited(&reader, (uintmax_t)INT64_MAX,
                                      &price_input)) {
                fputs("Invalid stock price\n", stderr);
                goto cleanup;
            }

            prices[i] = (int64_t)price_input;
        }

        if (!input_reader_finish(&reader)) {
            fputs("Invalid trailing input\n", stderr);
            goto cleanup;
        }

        if (!max_profit(prices, count, max_transactions, &profit)) {
            fputs("Unable to calculate profit\n", stderr);
            goto cleanup;
        }
    }

    if (printf("%" PRId64 "\n", profit) < 0 ||
        fflush(stdout) == EOF) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(prices);
    return exit_status;
}