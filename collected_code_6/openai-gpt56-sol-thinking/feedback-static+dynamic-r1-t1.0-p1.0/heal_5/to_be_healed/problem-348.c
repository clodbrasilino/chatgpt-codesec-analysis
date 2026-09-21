#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    bool error;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
} InputReader;

static int input_read_byte(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL || reader->error) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1U, sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                reader->error = true;
            }
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static bool read_size_value(InputReader *reader, size_t *value)
{
    int c;
    size_t parsed = 0;

    if (reader == NULL || value == NULL) {
        return false;
    }

    do {
        c = input_read_byte(reader);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == '+') {
        c = input_read_byte(reader);
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return false;
    }

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (parsed > (SIZE_MAX - digit) / 10U) {
            return false;
        }

        parsed = parsed * 10U + digit;
        c = input_read_byte(reader);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (reader->error) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *value)
{
    int c;
    bool negative = false;
    uintmax_t magnitude = 0;
    uintmax_t limit;

    if (reader == NULL || value == NULL) {
        return false;
    }

    do {
        c = input_read_byte(reader);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == '-' || c == '+') {
        negative = c == '-';
        c = input_read_byte(reader);
    }

    if (c == EOF || !isdigit((unsigned char)c)) {
        return false;
    }

    limit = negative
        ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
        : (uintmax_t)INT64_MAX;

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;
        c = input_read_byte(reader);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return false;
    }

    if (reader->error) {
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

static bool count_sequences(const int64_t *values, size_t value_count,
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
    uint64_t total = UINT64_C(0);
    bool success = false;

    if (result == NULL || (values == NULL && value_count != 0)) {
        return false;
    }

    *result = UINT64_C(0);

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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(unique_values, values, value_count * sizeof(*unique_values));
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
                goto cleanup;
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

        success = true;
        goto cleanup;
    }

    if (length > (SIZE_MAX - 1U) / max_positive) {
        goto cleanup;
    }

    max_sum = length * max_positive;
    width = max_sum + 1U;

    if (width > SIZE_MAX / sizeof(*current)) {
        goto cleanup;
    }

    bytes = width * sizeof(*current);

    current = calloc(width, sizeof(*current));
    next = calloc(width, sizeof(*next));

    if (current == NULL || next == NULL) {
        goto cleanup;
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
                        (uintmax_t)(-(selected + INT64_C(1))) + UINTMAX_C(1);

                    if ((uintmax_t)sum < magnitude) {
                        continue;
                    }

                    next_sum = sum - (size_t)magnitude;
                }

                if (ways > UINT64_MAX - next[next_sum]) {
                    goto cleanup;
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
            goto cleanup;
        }

        total += current[sum];
    }

    *result = total;
    success = true;

cleanup:
    free(current);
    free(next);
    free(unique_values);
    return success;
}

int main(void)
{
    InputReader reader = {
        .stream = stdin,
        .error = false,
        .buffer = {0},
        .position = 0,
        .length = 0
    };
    size_t value_count;
    size_t length;
    int64_t *values = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (!read_size_value(&reader, &value_count) ||
        !read_size_value(&reader, &length)) {
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
        if (!read_int64_value(&reader, &values[i])) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }
    }

    if (!count_sequences(values, value_count, length, &result)) {
        fputs("Unable to count sequences\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    return status;
}