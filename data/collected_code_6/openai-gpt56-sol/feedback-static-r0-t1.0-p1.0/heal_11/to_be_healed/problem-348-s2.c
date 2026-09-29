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

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size_value(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '-' || token[0] == '\0') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(token);
        return 0;
    }

    *value = (size_t)parsed;
    free(token);
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return 0;
    }

    *value = (int64_t)parsed;
    free(token);
    return 1;
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

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        return 0;
    }
#endif

    if ((uint64_t)max_value > UINT64_MAX / (uint64_t)length) {
        return 0;
    }

    max_sum_u = (uint64_t)max_value * (uint64_t)length;

#if UINT64_MAX > SIZE_MAX
    if (max_sum_u > SIZE_MAX) {
        return 0;
    }
#endif

    max_sum = (size_t)max_sum_u;

    if (max_sum == SIZE_MAX ||
        max_sum + 1 > SIZE_MAX / sizeof(*current)) {
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
        uint64_t current_limit_u =
            (uint64_t)max_value * (uint64_t)position;
        uint64_t next_limit_u = current_limit_u + (uint64_t)max_value;
        size_t current_limit = (size_t)current_limit_u;
        size_t next_limit = (size_t)next_limit_u;

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

                    if (candidate > next_limit_u) {
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

                if (new_sum > next_limit ||
                    !add_count(&next[new_sum], current[sum])) {
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

    if (!read_size_value(&value_count) ||
        !read_size_value(&length)) {
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

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}