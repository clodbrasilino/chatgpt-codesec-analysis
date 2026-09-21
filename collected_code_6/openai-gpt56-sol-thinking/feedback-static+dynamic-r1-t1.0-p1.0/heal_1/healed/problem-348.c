#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static int compare_int64(const void *left, const void *right)
{
    int64_t a = *(const int64_t *)left;
    int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static bool read_size_value(size_t *value)
{
    int c;
    size_t parsed = 0;

    if (value == NULL) {
        return false;
    }

    do {
        c = getchar();
    } while (c != EOF && isspace((unsigned char)c));

    if (c == '+') {
        c = getchar();
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return false;
    }

    while (c != EOF && isdigit((unsigned char)c)) {
        unsigned int digit = (unsigned int)(c - '0');

        if (parsed > (SIZE_MAX - digit) / 10) {
            return false;
        }

        parsed = parsed * 10 + digit;
        c = getchar();
    }

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (c == EOF && ferror(stdin)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(int64_t *value)
{
    int c;
    bool negative = false;
    uintmax_t magnitude = 0;
    uintmax_t limit;

    if (value == NULL) {
        return false;
    }

    do {
        c = getchar();
    } while (c != EOF && isspace((unsigned char)c));

    if (c == '-' || c == '+') {
        negative = c == '-';
        c = getchar();
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return false;
    }

    limit = negative
        ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
        : (uintmax_t)INT64_MAX;

    while (c != EOF && isdigit((unsigned char)c)) {
        unsigned int digit = (unsigned int)(c - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;
        c = getchar();
    }

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (c == EOF && ferror(stdin)) {
        return false;
    }

    if (negative) {
        if (magnitude == (uintmax_t)INT64_MAX + UINTMAX_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

bool count_sequences(const int64_t *values, size_t value_count,
                     size_t length, uint64_t *result)
{
    int64_t *unique_values = NULL;
    uint64_t *current = NULL;
    uint64_t *next = NULL;
    size_t unique_count = 0;
    size_t max_positive = 0;
    size_t max_sum;
    size_t width;
    size_t bytes;
    uint64_t total = 0;

    if (result == NULL || (values == NULL && value_count != 0)) {
        return false;
    }

    *result = 0;

    if (length == 0) {
        *result = UINT64_C(1);
        return true;
    }

    if (value_count == 0) {
        return true;
    }

    if (value_count > SIZE_MAX / sizeof(*unique_values)) {
        return false;
    }

    unique_values = malloc(value_count * sizeof(*unique_values));
    if (unique_values == NULL) {
        return false;
    }

    for (size_t i = 0; i < value_count; ++i) {
        unique_values[i] = values[i];
    }

    qsort(unique_values, value_count, sizeof(*unique_values), compare_int64);

    for (size_t i = 0; i < value_count; ++i) {
        if (i == 0 || unique_values[i] != unique_values[i - 1]) {
            unique_values[unique_count++] = unique_values[i];
        }
    }

    for (size_t i = 0; i < unique_count; ++i) {
        if (unique_values[i] > 0) {
            uintmax_t positive = (uintmax_t)unique_values[i];

            if (positive > (uintmax_t)SIZE_MAX) {
                free(unique_values);
                return false;
            }

            if ((size_t)positive > max_positive) {
                max_positive = (size_t)positive;
            }
        }
    }

    if (max_positive == 0) {
        for (size_t i = 0; i < unique_count; ++i) {
            if (unique_values[i] == 0) {
                *result = UINT64_C(1);
                break;
            }
        }

        free(unique_values);
        return true;
    }

    if (length > (SIZE_MAX - 1) / max_positive) {
        free(unique_values);
        return false;
    }

    max_sum = length * max_positive;
    width = max_sum + 1;

    if (width > SIZE_MAX / sizeof(*current)) {
        free(unique_values);
        return false;
    }

    bytes = width * sizeof(*current);

    current = calloc(width, sizeof(*current));
    next = calloc(width, sizeof(*next));

    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        free(unique_values);
        return false;
    }

    current[0] = UINT64_C(1);

    for (size_t position = 0; position < length; ++position) {
        size_t current_limit = position * max_positive;

        memset(next, 0, bytes);

        for (size_t sum = 0; sum <= current_limit; ++sum) {
            uint64_t ways = current[sum];

            if (ways == 0) {
                continue;
            }

            for (size_t i = 0; i < unique_count; ++i) {
                int64_t selected = unique_values[i];
                size_t next_sum;

                if (selected >= 0) {
                    size_t increase = (size_t)selected;

                    if (increase > max_sum - sum) {
                        continue;
                    }

                    next_sum = sum + increase;
                } else {
                    uintmax_t magnitude =
                        (uintmax_t)(-(selected + 1)) + UINTMAX_C(1);

                    if ((uintmax_t)sum < magnitude) {
                        continue;
                    }

                    next_sum = sum - (size_t)magnitude;
                }

                if (ways > UINT64_MAX - next[next_sum]) {
                    free(current);
                    free(next);
                    free(unique_values);
                    return false;
                }

                next[next_sum] += ways;
            }
        }

        {
            uint64_t *temporary = current;
            current = next;
            next = temporary;
        }
    }

    for (size_t sum = 0; sum <= max_sum; ++sum) {
        if (current[sum] > UINT64_MAX - total) {
            free(current);
            free(next);
            free(unique_values);
            return false;
        }

        total += current[sum];
    }

    *result = total;

    free(current);
    free(next);
    free(unique_values);
    return true;
}

int main(void)
{
    size_t value_count;
    size_t length;
    int64_t *values = NULL;
    uint64_t result;

    if (!read_size_value(&value_count) || !read_size_value(&length)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (!read_int64_value(&values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_sequences(values, value_count, length, &result)) {
        fputs("Unable to count sequences\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);

    free(values);
    return EXIT_SUCCESS;
}