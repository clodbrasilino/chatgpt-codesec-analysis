#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static unsigned long long count_sequences(const int *values, size_t value_count, size_t length)
{
    if (values == NULL || value_count == 0U) {
        return 0ULL;
    }

    int max_value = values[0];
    for (size_t i = 1U; i < value_count; ++i) {
        if (values[i] > max_value) {
            max_value = values[i];
        }
    }

    size_t max_sum = 0U;
    if (max_value > 0 && length > 0U) {
        if ((size_t)max_value > SIZE_MAX / length) {
            return 0ULL;
        }
        max_sum = (size_t)max_value * length;
        if (max_sum > (size_t)LLONG_MAX) {
            return 0ULL;
        }
    }

    unsigned long long *dp = calloc(max_sum + 1U, sizeof(*dp));
    unsigned long long *next = calloc(max_sum + 1U, sizeof(*next));
    if (dp == NULL || next == NULL) {
        free(dp);
        free(next);
        return 0ULL;
    }

    dp[0] = 1ULL;

    for (size_t pos = 0U; pos < length; ++pos) {
        memset(next, 0, (max_sum + 1U) * sizeof(*next));
        for (size_t sum = 0U; sum <= max_sum; ++sum) {
            const unsigned long long ways = dp[sum];
            if (ways == 0ULL) {
                continue;
            }
            for (size_t i = 0U; i < value_count; ++i) {
                const long long new_sum = (long long)sum + (long long)values[i];
                if (new_sum < 0LL || (unsigned long long)new_sum > (unsigned long long)max_sum) {
                    continue;
                }
                next[(size_t)new_sum] += ways;
            }
        }
        unsigned long long *swap = dp;
        dp = next;
        next = swap;
    }

    unsigned long long total = 0ULL;
    for (size_t sum = 0U; sum <= max_sum; ++sum) {
        total += dp[sum];
    }

    free(dp);
    free(next);

    return total;
}

int main(void)
{
    size_t value_count = 0U;
    size_t length = 0U;

    if (scanf("%zu", &value_count) != 1 || value_count == 0U || value_count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid number of values\n");
        return EXIT_FAILURE;
    }

    int *values = malloc(value_count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < value_count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fprintf(stderr, "Invalid value\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid length\n");
        free(values);
        return EXIT_FAILURE;
    }

    printf("%llu\n", count_sequences(values, value_count, length));

    free(values);
    return EXIT_SUCCESS;
}