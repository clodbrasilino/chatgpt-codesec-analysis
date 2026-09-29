#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
} InputReader;

static bool input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    return true;
}

static int input_reader_get(InputReader *reader, unsigned char *character)
{
    if (reader == NULL || reader->stream == NULL || character == NULL) {
        return -1;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, sizeof(reader->buffer[0]),
                               INPUT_BUFFER_SIZE, reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                return -1;
            }

            return feof(reader->stream) ? 0 : -1;
        }
    }

    *character = reader->buffer[reader->position];
    ++reader->position;
    return 1;
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
    } while (isspace((int)character));

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
        uintmax_t digit = (uintmax_t)(character - (unsigned char)'0');

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

    if (!isspace((int)character)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool add_nonnegative_int64(int64_t left, int64_t right,
                                  int64_t *result)
{
    if (result == NULL || left < 0 || right < 0 ||
        left > INT64_MAX - right) {
        return false;
    }

    *result = left + right;
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

                if (!add_nonnegative_int64(profit, gain, &profit)) {
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

    if (state_count > SIZE_MAX / sizeof(*buy) ||
        state_count > SIZE_MAX / sizeof(*sell)) {
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
        for (size_t transaction = max_transactions;
             transaction > 0;
             --transaction) {
            int64_t buy_candidate =
                sell[transaction - 1] - prices[day];

            if (buy_candidate > buy[transaction]) {
                buy[transaction] = buy_candidate;
            }

            if (buy[transaction] > INT64_MAX - prices[day]) {
                free(buy);
                free(sell);
                return false;
            }

            int64_t sell_candidate =
                buy[transaction] + prices[day];

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

    if (!input_reader_init(&reader, stdin)) {
        fputs("Unable to initialize input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_uintmax_limited(&reader, UINTMAX_MAX, &count_input) ||
        !read_uintmax_limited(&reader, UINTMAX_MAX,
                              &transactions_input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_input > (uintmax_t)SIZE_MAX ||
        transactions_input > (uintmax_t)SIZE_MAX) {
        fputs("Input is too large\n", stderr);
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

        if (!read_uintmax_limited(&reader, (uintmax_t)INT64_MAX,
                                  &price_input)) {
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
        free(prices);
        return EXIT_FAILURE;
    }

    free(prices);
    return EXIT_SUCCESS;
}