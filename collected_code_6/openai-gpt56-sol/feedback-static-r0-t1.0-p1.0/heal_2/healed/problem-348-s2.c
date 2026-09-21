#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_count(uint64_t *target, uint64_t value)
{
    if (UINT64_MAX - *target < value) {
        return 0;
    }

    *target += value;
    return 1;
}

static int read_size_value(size_t *value)
{
    char token[128];
    char *end;
    uintmax_t parsed;

    if (fscanf(stdin, "%127s", token) != 1 || token[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char token[128];
    char *end;
    intmax_t parsed;

    if (fscanf(stdin, "%127s", token) != 1) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
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

    if (max_sum_u > SIZE_MAX - 1) {
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

    if (!read_size_value(&value_count) || !read_size_value(&length)) {
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