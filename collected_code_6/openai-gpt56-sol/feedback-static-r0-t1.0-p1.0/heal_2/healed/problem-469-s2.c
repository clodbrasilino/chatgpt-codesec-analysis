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

static void discard_line(void)
{
    int character;

    do {
        character = getchar();
    } while (character != '\n' && character != EOF);
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0U;
    int character;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    *line = NULL;
    *capacity = 0U;

    for (;;) {
        character = getchar();

        if (character == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(*line);
                *line = NULL;
                *capacity = 0U;
                return 0;
            }
            break;
        }

        if (length > SIZE_MAX - 2U) {
            free(*line);
            *line = NULL;
            *capacity = 0U;
            discard_line();
            return 0;
        }

        if (length + 1U >= *capacity) {
            size_t new_capacity;
            char *replacement;

            if (*capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (*capacity > SIZE_MAX / 2U) {
                    free(*line);
                    *line = NULL;
                    *capacity = 0U;
                    discard_line();
                    return 0;
                }
                new_capacity = *capacity * 2U;
            }

            replacement = realloc(*line, new_capacity);
            if (replacement == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0U;
                discard_line();
                return 0;
            }

            *line = replacement;
            *capacity = new_capacity;
        }

        if (character == '\n') {
            break;
        }

        (*line)[length++] = (char)character;
    }

    if (*line == NULL) {
        *line = malloc(1U);
        if (*line == NULL) {
            return 0;
        }
        *capacity = 1U;
    }

    (*line)[length] = '\0';
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

static int read_size_value(size_t *value)
{
    char *input;
    char *end;
    size_t capacity;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&input, &capacity)) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    valid = errno != ERANGE &&
            end != input &&
            input[0] != '-' &&
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
    size_t capacity;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&input, &capacity)) {
        return 0;
    }

    errno = 0;
    end = NULL;
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

    if (result == NULL) {
        return 0;
    }

    *result = 0;

    if (count < 2U || k == 0U) {
        return 1;
    }

    if (prices == NULL) {
        return 0;
    }

    if (k >= count / 2U) {
        int64_t profit = 0;

        for (size_t i = 1U; i < count; ++i) {
            if (prices[i] > prices[i - 1U]) {
                int64_t difference;

                if (!subtract_int64(prices[i], prices[i - 1U], &difference) ||
                    !add_int64(profit, difference, &profit)) {
                    return 0;
                }
            }
        }

        *result = profit;
        return 1;
    }

    if (k == SIZE_MAX || k + 1U > SIZE_MAX / sizeof(int64_t)) {
        return 0;
    }

    previous = calloc(k + 1U, sizeof(*previous));
    current = calloc(k + 1U, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return 0;
    }

    for (size_t day = 1U; day < count; ++day) {
        int64_t best_difference = -prices[0];

        current[0] = 0;

        for (size_t transaction = 1U; transaction <= k; ++transaction) {
            int64_t sell_profit;
            int64_t candidate;

            if (!add_int64(prices[day], best_difference, &sell_profit) ||
                !subtract_int64(previous[transaction - 1U],
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
        count == 0U ||
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

    for (size_t i = 0U; i < count; ++i) {
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