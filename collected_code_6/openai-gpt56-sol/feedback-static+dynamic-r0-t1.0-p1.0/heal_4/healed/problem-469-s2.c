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

static int parse_uintmax(uintmax_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    start = line;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
    return 1;
}

static int read_size_value(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        !parse_uintmax(&parsed) ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_nonnegative_int64(int64_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        !parse_uintmax(&parsed) ||
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
    size_t bytes;

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

    bytes = elements * sizeof(*previous);
    previous = calloc(elements, sizeof(*previous));
    current = calloc(elements, sizeof(*current));
    best_difference = malloc(bytes);

    if (previous == NULL || current == NULL || best_difference == NULL) {
        free(previous);
        free(current);
        free(best_difference);
        return 0;
    }

    best_difference[0] = 0;

    for (size_t transaction = 1; transaction <= k; ++transaction) {
        if (!checked_sub(0, prices[0], &best_difference[transaction])) {
            free(previous);
            free(current);
            free(best_difference);
            return 0;
        }
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