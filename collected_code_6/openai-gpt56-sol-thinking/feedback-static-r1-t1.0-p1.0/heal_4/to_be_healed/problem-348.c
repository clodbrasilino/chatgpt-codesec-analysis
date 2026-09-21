#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
} InputReader;

static int input_get_character(InputReader *reader)
{
    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1, sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            return EOF;
        }
    }

    return reader->buffer[reader->position++];
}

static int input_get_nonspace_character(InputReader *reader)
{
    int character;

    do {
        character = input_get_character(reader);
    } while (character != EOF &&
             isspace((unsigned char)character));

    return character;
}

static bool read_size_value(InputReader *reader, size_t *value)
{
    size_t parsed = 0;
    bool valid = true;
    bool have_digit = false;
    bool negative = false;
    int character;

    if (reader == NULL || value == NULL) {
        return false;
    }

    character = input_get_nonspace_character(reader);
    if (character == EOF) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_get_character(reader);
    }

    while (character != EOF &&
           !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            size_t digit = (size_t)(character - '0');

            have_digit = true;

            if (parsed > (SIZE_MAX - digit) / 10) {
                valid = false;
            } else {
                parsed = parsed * 10 + digit;
            }
        } else {
            valid = false;
        }

        character = input_get_character(reader);
    }

    if (!valid || !have_digit || negative) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *value)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    bool valid = true;
    bool have_digit = false;
    bool negative = false;
    int character;

    if (reader == NULL || value == NULL) {
        return false;
    }

    character = input_get_nonspace_character(reader);
    if (character == EOF) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_get_character(reader);
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    while (character != EOF &&
           !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uint64_t digit = (uint64_t)(character - '0');

            have_digit = true;

            if (magnitude > (limit - digit) / UINT64_C(10)) {
                valid = false;
            } else {
                magnitude = magnitude * UINT64_C(10) + digit;
            }
        } else {
            valid = false;
        }

        character = input_get_character(reader);
    }

    if (!valid || !have_digit) {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

bool count_sequences(const int64_t *values, size_t value_count,
                     size_t length, uint64_t *result)
{
    int64_t *unique_values = NULL;
    uint64_t *current = NULL;
    uint64_t *next = NULL;
    uint64_t total = 0;
    size_t unique_count = 0;
    size_t max_positive = 0;
    size_t max_sum;
    size_t width;
    size_t bytes;

    if (result == NULL ||
        (values == NULL && value_count != 0)) {
        return false;
    }

    *result = 0;

    if (length == 0) {
        *result = 1;
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

    qsort(unique_values, value_count, sizeof(*unique_values),
          compare_int64);

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
                *result = 1;
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

    current[0] = 1;

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

                    if (magnitude > (uintmax_t)sum) {
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
    InputReader reader = {
        .stream = stdin,
        .position = 0,
        .length = 0
    };
    size_t value_count;
    size_t length;
    int64_t *values = NULL;
    uint64_t result;

    if (!read_size_value(&reader, &value_count) ||
        !read_size_value(&reader, &length)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (!read_int64_value(&reader, &values[i])) {
            fprintf(stderr, "Invalid input\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_sequences(values, value_count, length, &result)) {
        fprintf(stderr, "Unable to count sequences\n");
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);

    free(values);
    return EXIT_SUCCESS;
}