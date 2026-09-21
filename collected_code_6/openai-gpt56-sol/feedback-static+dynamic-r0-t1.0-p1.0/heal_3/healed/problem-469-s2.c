#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int checked_add(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_sub(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return 0;
    }

    *result = a - b;
    return 1;
}

static int discard_token(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        ch = fgetc(stdin);
    }

    return ch;
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        buffer[0] = '\0';
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1) {
            buffer[0] = '\0';
            discard_token(ch);
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    buffer[length] = '\0';
    return 1;
}

static int parse_uintmax(uintmax_t *value)
{
    char buffer[sizeof(uintmax_t) * CHAR_BIT + 2];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_size_value(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !parse_uintmax(&parsed) ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_nonnegative_int64(int64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !parse_uintmax(&parsed) ||
        parsed > (uintmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int max_profit(const int64_t *prices, size_t count, size_t k,
                      int64_t *result)
{
    int64_t *previous = NULL;
    int64_t *current = NULL;
    int64_t *best_difference = NULL;
    size_t elements;

    if (result == NULL) {
        return 0;
    }

    *result = 0;

    if (count < 2 || k == 0) {
        return 1;
    }

    if (prices == NULL) {
        return 0;
    }

    if (k >= count / 2) {
        int64_t profit = 0;

        for (size_t i = 1; i < count; ++i) {
            if (prices[i] > prices[i - 1]) {
                int64_t gain;

                if (!checked_sub(prices[i], prices[i - 1], &gain) ||
                    !checked_add(profit, gain, &profit)) {
                    return 0;
                }
            }
        }

        *result = profit;
        return 1;
    }

    if (k == SIZE_MAX) {
        return 0;
    }

    elements = k + 1;

    if (elements > SIZE_MAX / sizeof(*previous)) {
        return 0;
    }

    previous = calloc(elements, sizeof(*previous));
    current = calloc(elements, sizeof(*current));
    best_difference = malloc(elements * sizeof(*best_difference));

    if (previous == NULL || current == NULL || best_difference == NULL) {
        free(previous);
        free(current);
        free(best_difference);
        return 0;
    }

    best_difference[0] = 0;

    for (size_t transaction = 1; transaction <= k; ++transaction) {
        best_difference[transaction] = -prices[0];
    }

    for (size_t day = 1; day < count; ++day) {
        current[0] = 0;

        for (size_t transaction = 1; transaction <= k; ++transaction) {
            int64_t sell_profit;
            int64_t candidate;

            if (!checked_add(prices[day],
                             best_difference[transaction],
                             &sell_profit) ||
                !checked_sub(previous[transaction - 1],
                             prices[day],
                             &candidate)) {
                free(previous);
                free(current);
                free(best_difference);
                return 0;
            }

            current[transaction] =
                previous[transaction] > sell_profit
                    ? previous[transaction]
                    : sell_profit;

            if (candidate > best_difference[transaction]) {
                best_difference[transaction] = candidate;
            }
        }

        {
            int64_t *temporary = previous;
            previous = current;
            current = temporary;
        }
    }

    *result = previous[k];

    free(previous);
    free(current);
    free(best_difference);
    return 1;
}

int main(void)
{
    size_t count;
    size_t k;
    int64_t *prices;
    int64_t profit;

    if (!read_size_value(&count) ||
        !read_size_value(&k) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*prices)) {
        return EXIT_FAILURE;
    }

    prices = malloc(count * sizeof(*prices));

    if (prices == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_nonnegative_int64(&prices[i])) {
            free(prices);
            return EXIT_FAILURE;
        }
    }

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