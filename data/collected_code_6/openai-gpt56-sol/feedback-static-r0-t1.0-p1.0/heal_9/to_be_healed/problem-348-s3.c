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

static uint64_t negative_magnitude_i64(int64_t value)
{
    return (uint64_t)(-(value + 1)) + UINT64_C(1);
}

static int count_sequences(const int64_t *values, size_t value_count,
                           size_t length, uint64_t *result)
{
    int64_t min_value = 0;
    int64_t max_value = 0;
    size_t negative_span;
    size_t positive_span;
    size_t range;
    size_t zero_index;
    uint64_t *current = NULL;
    uint64_t *next = NULL;

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

    if (length == 0) {
        negative_span = 0;
        positive_span = 0;
    } else {
        uint64_t negative_magnitude =
            min_value < 0 ? negative_magnitude_i64(min_value) : UINT64_C(0);
        uint64_t positive_magnitude =
            max_value > 0 ? (uint64_t)max_value : UINT64_C(0);

        if (negative_magnitude > (uint64_t)SIZE_MAX / length ||
            positive_magnitude > (uint64_t)SIZE_MAX / length) {
            return 0;
        }

        negative_span = (size_t)negative_magnitude * length;
        positive_span = (size_t)positive_magnitude * length;
    }

    if (negative_span > SIZE_MAX - positive_span) {
        return 0;
    }

    range = negative_span + positive_span;

    if (range == SIZE_MAX) {
        return 0;
    }

    ++range;
    zero_index = negative_span;

    if (range > SIZE_MAX / sizeof(*current)) {
        return 0;
    }

    current = calloc(range, sizeof(*current));
    next = calloc(range, sizeof(*next));

    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        return 0;
    }

    current[zero_index] = UINT64_C(1);

    for (size_t step = 0; step < length; ++step) {
        for (size_t i = 0; i < range; ++i) {
            next[i] = UINT64_C(0);
        }

        for (size_t index = 0; index < range; ++index) {
            if (current[index] == UINT64_C(0)) {
                continue;
            }

            for (size_t j = 0; j < value_count; ++j) {
                size_t next_index;

                if (values[j] >= 0) {
                    uint64_t offset = (uint64_t)values[j];

                    if (offset > (uint64_t)(SIZE_MAX - index)) {
                        continue;
                    }

                    next_index = index + (size_t)offset;

                    if (next_index >= range) {
                        continue;
                    }
                } else {
                    uint64_t offset = negative_magnitude_i64(values[j]);

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

    *result = UINT64_C(0);

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

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int character;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        if (character == EOF || isspace((unsigned char)character)) {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t input;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    input = strtoumax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            input <= (uintmax_t)SIZE_MAX;

    if (valid) {
        *value = (size_t)input;
    }

    free(buffer);
    return valid;
}

static int read_i64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t input;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    input = strtoimax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            input >= INT64_MIN &&
            input <= INT64_MAX;

    if (valid) {
        *value = (int64_t)input;
    }

    free(buffer);
    return valid;
}

int main(void)
{
    size_t value_count;
    size_t length;
    int64_t *values;
    uint64_t result;

    if (!read_size(&value_count) ||
        !read_size(&length) ||
        value_count == 0 ||
        value_count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(value_count * sizeof(*values));
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

    free(values);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}