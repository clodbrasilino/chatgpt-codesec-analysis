#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_count(uint64_t *target, uint64_t value)
{
    if (target == NULL || value > UINT64_MAX - *target) {
        return 0;
    }

    *target += value;
    return 1;
}

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        char *replacement = malloc(128);

        if (replacement == NULL) {
            return 0;
        }

        free(*line);
        *line = replacement;
        *capacity = 128;
    }

    for (;;) {
        int ch;

        if (length == SIZE_MAX - 1) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity = *capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            if (new_capacity < required) {
                return 0;
            }

            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return 0;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        (*line)[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
    return 1;
}

static void skip_space(const char **cursor)
{
    if (cursor == NULL || *cursor == NULL) {
        return;
    }

    while (**cursor != '\0' &&
           isspace((unsigned char)**cursor) != 0) {
        ++*cursor;
    }
}

static int at_end(const char *cursor)
{
    if (cursor == NULL) {
        return 0;
    }

    skip_space(&cursor);
    return *cursor == '\0';
}

static int parse_size(const char **cursor, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    skip_space(cursor);

    if (**cursor == '\0' || **cursor == '-' || **cursor == '+') {
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

static int parse_int64(const char **cursor, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    skip_space(cursor);

    if (**cursor == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (int64_t)parsed;
    return 1;
}

static int read_sizes(size_t *value_count, size_t *length)
{
    char *line = NULL;
    size_t capacity = 0;
    const char *cursor;
    int success;

    if (value_count == NULL || length == NULL) {
        return 0;
    }

    if (!read_line(stdin, &line, &capacity)) {
        free(line);
        return 0;
    }

    cursor = line;
    success = parse_size(&cursor, value_count) &&
              parse_size(&cursor, length) &&
              at_end(cursor);

    free(line);
    return success;
}

static int read_int64_value(int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    const char *cursor;
    int success;

    if (value == NULL) {
        return 0;
    }

    if (!read_line(stdin, &line, &capacity)) {
        free(line);
        return 0;
    }

    cursor = line;
    success = parse_int64(&cursor, value) && at_end(cursor);

    free(line);
    return success;
}

static int count_sequences(const int64_t *values, size_t value_count,
                           size_t length, uint64_t *result)
{
    int64_t max_value = 0;
    uint64_t max_sum_u;
    size_t max_sum;
    uint64_t *current = NULL;
    uint64_t *next = NULL;

    if (result == NULL || (value_count != 0 && values == NULL)) {
        return 0;
    }

    *result = 0;

    if (length == 0) {
        *result = 1;
        return 1;
    }

    if (value_count == 0) {
        return 1;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (values[i] > max_value) {
            max_value = values[i];
        }
    }

    if (max_value <= 0) {
        *result = max_value == 0 ? 1 : 0;
        return 1;
    }

    if ((uint64_t)length > UINT64_MAX / (uint64_t)max_value) {
        return 0;
    }

    max_sum_u = (uint64_t)max_value * (uint64_t)length;

    if (max_sum_u >= SIZE_MAX) {
        return 0;
    }

    max_sum = (size_t)max_sum_u;

    if (max_sum + 1 > SIZE_MAX / sizeof(*current)) {
        return 0;
    }

    current = calloc(max_sum + 1, sizeof(*current));
    next = calloc(max_sum + 1, sizeof(*next));

    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        return 0;
    }

    current[0] = 1;

    for (size_t position = 0; position < length; ++position) {
        size_t current_limit =
            (size_t)((uint64_t)max_value * (uint64_t)position);
        size_t next_limit =
            (size_t)((uint64_t)max_value * ((uint64_t)position + 1));

        for (size_t i = 0; i <= next_limit; ++i) {
            next[i] = 0;
        }

        for (size_t sum = 0; sum <= current_limit; ++sum) {
            if (current[sum] == 0) {
                continue;
            }

            for (size_t i = 0; i < value_count; ++i) {
                size_t new_sum;

                if (values[i] >= 0) {
                    uint64_t candidate =
                        (uint64_t)sum + (uint64_t)values[i];

                    if (candidate > (uint64_t)next_limit) {
                        continue;
                    }

                    new_sum = (size_t)candidate;
                } else {
                    uint64_t magnitude =
                        values[i] == INT64_MIN
                            ? (uint64_t)INT64_MAX + UINT64_C(1)
                            : (uint64_t)(-values[i]);

                    if (magnitude > (uint64_t)sum) {
                        continue;
                    }

                    new_sum = sum - (size_t)magnitude;
                }

                if (!add_count(&next[new_sum], current[sum])) {
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

    for (size_t sum = 0; sum <= max_sum; ++sum) {
        if (!add_count(result, current[sum])) {
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
    int64_t *values = NULL;
    uint64_t result;

    if (!read_sizes(&value_count, &length)) {
        return EXIT_FAILURE;
    }

    if (value_count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (!read_int64_value(&values[i])) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_sequences(values, value_count, length, &result)) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}