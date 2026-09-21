#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int subtract_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return 0;
    }

    *result = a - b;
    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *replacement;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            replacement = realloc(buffer, new_capacity);
            if (replacement == NULL) {
                free(buffer);
                return 0;
            }

            buffer = replacement;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int trailing_characters_valid(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0' && isspace((unsigned char)*text)) {
        ++text;
    }

    return *text == '\0';
}

static int has_negative_sign(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0' && isspace((unsigned char)*text)) {
        ++text;
    }

    return *text == '-';
}

static int read_size_value(size_t *value)
{
    char *input;
    char *end;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&input)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    valid = errno != ERANGE &&
            end != input &&
            !has_negative_sign(input) &&
            parsed <= SIZE_MAX &&
            trailing_characters_valid(end);

    if (valid) {
        *value = (size_t)parsed;
    }

    free(input);
    return valid;
}

static int read_price(int64_t *value)
{
    char *input;
    char *end;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&input)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(input, &end, 10);

    valid = errno != ERANGE &&
            end != input &&
            parsed >= 0 &&
            parsed <= INT64_MAX &&
            trailing_characters_valid(end);

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(input);
    return valid;
}

static int max_profit(const int64_t *prices, size_t count, size_t k,
                      int64_t *result)
{
    int64_t *previous;
    int64_t *current;
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
                int64_t difference;

                if (!subtract_int64(prices[i], prices[i - 1], &difference) ||
                    !add_int64(profit, difference, &profit)) {
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

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return 0;
    }

    for (size_t day = 1; day < count; ++day) {
        int64_t best_difference;

        if (!subtract_int64(0, prices[0], &best_difference)) {
            free(previous);
            free(current);
            return 0;
        }

        current[0] = 0;

        for (size_t transaction = 1; transaction <= k; ++transaction) {
            int64_t sell_profit;
            int64_t candidate;

            if (!add_int64(prices[day], best_difference, &sell_profit) ||
                !subtract_int64(previous[transaction - 1],
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

        {
            int64_t *temporary = previous;
            previous = current;
            current = temporary;
        }
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
    int64_t *prices;
    int64_t profit;

    if (!read_size_value(&count) ||
        count == 0 ||
        !read_size_value(&k)) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*prices)) {
        return EXIT_FAILURE;
    }

    prices = malloc(count * sizeof(*prices));
    if (prices == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_price(&prices[i])) {
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