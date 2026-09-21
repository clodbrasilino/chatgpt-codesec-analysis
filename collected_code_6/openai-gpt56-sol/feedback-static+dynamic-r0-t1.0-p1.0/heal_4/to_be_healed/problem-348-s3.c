#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || b > UINT64_MAX - a) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

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

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static void skip_space(char **cursor)
{
    while (**cursor != '\0' &&
           isspace((unsigned char)**cursor)) {
        ++*cursor;
    }
}

static int parse_size(char **cursor, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    skip_space(cursor);

    if (**cursor == '\0' || **cursor == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || parsed > SIZE_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (size_t)parsed;
    return 1;
}

static int read_sizes(size_t *first, size_t *second)
{
    char *line;
    char *cursor;
    int valid;

    if (first == NULL || second == NULL || !read_line(&line)) {
        return 0;
    }

    cursor = line;
    valid = parse_size(&cursor, first) &&
            parse_size(&cursor, second);

    if (valid) {
        skip_space(&cursor);
        valid = *cursor == '\0';
    }

    free(line);
    return valid;
}

static int read_i64(int64_t *value)
{
    char *line;
    char *cursor;
    char *end;
    intmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    cursor = line;
    skip_space(&cursor);

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);

    if (end != cursor && errno != ERANGE &&
        parsed >= INT64_MIN && parsed <= INT64_MAX) {
        cursor = end;
        skip_space(&cursor);

        if (*cursor == '\0') {
            *value = (int64_t)parsed;
            valid = 1;
        }
    }

    free(line);
    return valid;
}

static uint64_t magnitude_i64(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + 1)) + UINT64_C(1);
}

static int count_sequences(const int64_t *values, size_t value_count,
                           size_t length, uint64_t *result)
{
    int64_t min_value = 0;
    int64_t max_value = 0;
    uint64_t negative_magnitude;
    uint64_t positive_magnitude;
    size_t negative_span;
    size_t positive_span;
    size_t range;
    size_t zero_index;
    uint64_t *current;
    uint64_t *next;

    if (values == NULL || value_count == 0 || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (values[i] < min_value) {
            min_value = values[i];
        }
        if (values[i] > max_value) {
            max_value = values[i];
        }
    }

    negative_magnitude = magnitude_i64(min_value);
    positive_magnitude = max_value > 0 ? (uint64_t)max_value : 0;

    if (length != 0 &&
        (negative_magnitude > (uint64_t)(SIZE_MAX / length) ||
         positive_magnitude > (uint64_t)(SIZE_MAX / length))) {
        return 0;
    }

    negative_span = (size_t)negative_magnitude * length;
    positive_span = (size_t)positive_magnitude * length;

    if (negative_span > SIZE_MAX - positive_span ||
        negative_span + positive_span == SIZE_MAX) {
        return 0;
    }

    range = negative_span + positive_span + 1;
    zero_index = negative_span;

    if (range > SIZE_MAX / sizeof *current) {
        return 0;
    }

    current = calloc(range, sizeof *current);
    next = calloc(range, sizeof *next);

    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        return 0;
    }

    current[zero_index] = UINT64_C(1);

    for (size_t step = 0; step < length; ++step) {
        for (size_t i = 0; i < range; ++i) {
            next[i] = 0;
        }

        for (size_t index = 0; index < range; ++index) {
            if (current[index] == 0) {
                continue;
            }

            for (size_t j = 0; j < value_count; ++j) {
                uint64_t offset = magnitude_i64(values[j]);
                size_t next_index;

                if (values[j] >= 0) {
                    if (offset > (uint64_t)(SIZE_MAX - index)) {
                        continue;
                    }

                    next_index = index + (size_t)offset;
                    if (next_index >= range) {
                        continue;
                    }
                } else {
                    if (offset > (uint64_t)index) {
                        continue;
                    }

                    next_index = index - (size_t)offset;
                }

                if (!add_u64(next[next_index], current[index],
                             &next[next_index])) {
                    free(current);
                    free(next);
                    return 0;
                }
            }
        }

        {
            uint64_t *temporary = current;
            current = next;
            next = temporary;
        }
    }

    *result = 0;

    for (size_t index = zero_index; index < range; ++index) {
        if (!add_u64(*result, current[index], result)) {
            free(current);
            free(next);
            return 0;
        }
    }

    free(current);
    free(next);
    return 1;
}

int main(void)
{
    size_t value_count;
    size_t length;
    int64_t *values;
    uint64_t result;

    if (!read_sizes(&value_count, &length) ||
        value_count == 0 ||
        value_count > SIZE_MAX / sizeof *values) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(value_count * sizeof *values);
    if (values == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (!read_i64(&values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_sequences(values, value_count, length, &result)) {
        fputs("Unable to compute result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}