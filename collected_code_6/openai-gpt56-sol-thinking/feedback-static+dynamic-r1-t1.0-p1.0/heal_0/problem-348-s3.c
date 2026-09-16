#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    COUNT_SUCCESS,
    COUNT_INVALID_ARGUMENT,
    COUNT_ALLOCATION_FAILURE,
    COUNT_OVERFLOW
} CountStatus;

CountStatus count_sequences(const int *values, size_t value_count,
                            size_t length, uint64_t *result)
{
    uint64_t *current;
    uint64_t *next;
    size_t max_positive = 0;
    size_t maximum_sum;
    size_t width;

    if (result == NULL || (values == NULL && value_count != 0)) {
        return COUNT_INVALID_ARGUMENT;
    }

    *result = 0;

    if (length == 0) {
        *result = 1;
        return COUNT_SUCCESS;
    }

    if (value_count == 0) {
        return COUNT_SUCCESS;
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (values[i] > 0 && (size_t)values[i] > max_positive) {
            max_positive = (size_t)values[i];
        }
    }

    if (max_positive != 0 && length > (SIZE_MAX - 1) / max_positive) {
        return COUNT_ALLOCATION_FAILURE;
    }

    maximum_sum = length * max_positive;
    width = maximum_sum + 1;

    if (width > SIZE_MAX / sizeof(*current)) {
        return COUNT_ALLOCATION_FAILURE;
    }

    current = calloc(width, sizeof(*current));
    next = calloc(width, sizeof(*next));

    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        return COUNT_ALLOCATION_FAILURE;
    }

    current[0] = 1;

    for (size_t position = 0; position < length; ++position) {
        size_t current_max = position * max_positive;
        size_t next_max = (position + 1) * max_positive;

        memset(next, 0, width * sizeof(*next));

        for (size_t sum = 0; sum <= current_max; ++sum) {
            if (current[sum] == 0) {
                continue;
            }

            for (size_t i = 0; i < value_count; ++i) {
                size_t new_sum;

                if (values[i] >= 0) {
                    size_t increment = (size_t)values[i];

                    if (increment > next_max - sum) {
                        continue;
                    }

                    new_sum = sum + increment;
                } else {
                    size_t decrement = (size_t)(-(int64_t)values[i]);

                    if (decrement > sum) {
                        continue;
                    }

                    new_sum = sum - decrement;
                }

                if (UINT64_MAX - next[new_sum] < current[sum]) {
                    free(current);
                    free(next);
                    return COUNT_OVERFLOW;
                }

                next[new_sum] += current[sum];
            }
        }

        {
            uint64_t *temporary = current;
            current = next;
            next = temporary;
        }
    }

    for (size_t sum = 0; sum <= maximum_sum; ++sum) {
        if (UINT64_MAX - *result < current[sum]) {
            free(current);
            free(next);
            return COUNT_OVERFLOW;
        }

        *result += current[sum];
    }

    free(current);
    free(next);
    return COUNT_SUCCESS;
}

int main(void)
{
    size_t value_count;
    size_t length;
    int *values = NULL;
    uint64_t result;
    CountStatus status;

    if (scanf("%zu %zu", &value_count, &length) != 2) {
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
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = count_sequences(values, value_count, length, &result);
    free(values);

    if (status == COUNT_ALLOCATION_FAILURE) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == COUNT_OVERFLOW) {
        fputs("Count overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != COUNT_SUCCESS) {
        fputs("Invalid argument\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}