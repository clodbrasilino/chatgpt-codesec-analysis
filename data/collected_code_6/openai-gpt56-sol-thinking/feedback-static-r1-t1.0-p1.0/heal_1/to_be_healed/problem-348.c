#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>

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
    size_t unique_count = 0;
    size_t max_positive = 0;
    size_t max_sum;
    size_t width;
    size_t bytes;

    if (result == NULL || (values == NULL && value_count != 0)) {
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
            uintmax_t value = (uintmax_t)unique_values[i];

            if (value > SIZE_MAX) {
                free(unique_values);
                return false;
            }

            if ((size_t)value > max_positive) {
                max_positive = (size_t)value;
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
                int64_t value = unique_values[i];
                size_t next_sum;

                if (value >= 0) {
                    size_t increase = (size_t)value;

                    if (sum > max_sum - increase) {
                        continue;
                    }

                    next_sum = sum + increase;
                } else {
                    uintmax_t magnitude =
                        (uintmax_t)(-(value + 1)) + UINTMAX_C(1);

                    if ((uintmax_t)sum < magnitude) {
                        continue;
                    }

                    next_sum = sum - (size_t)magnitude;
                }

                if (UINT64_MAX - next[next_sum] < ways) {
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
        if (UINT64_MAX - *result < current[sum]) {
            free(current);
            free(next);
            free(unique_values);
            return false;
        }

        *result += current[sum];
    }

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

    if (scanf("%zu %zu", &value_count, &length) != 2) {
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
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &values[i]) != 1) {
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