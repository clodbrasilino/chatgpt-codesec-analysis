#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    COUNT_SUCCESS,
    COUNT_INVALID_ARGUMENT,
    COUNT_ALLOCATION_FAILURE,
    COUNT_OVERFLOW
} CountStatus;

static bool checked_add(uint64_t *value, uint64_t increment)
{
    if (UINT64_MAX - *value < increment) {
        return false;
    }

    *value += increment;
    return true;
}

CountStatus count_subsequences_product_less_than_k(
    const uint64_t *array,
    size_t length,
    uint64_t k,
    uint64_t *result)
{
    uint64_t *counts;
    size_t state_count;

    if (result == NULL || (array == NULL && length != 0U)) {
        return COUNT_INVALID_ARGUMENT;
    }

    *result = 0;

    if (k == 0U || length == 0U) {
        return COUNT_SUCCESS;
    }

    if (k > SIZE_MAX || (size_t)k > SIZE_MAX / sizeof(*counts)) {
        return COUNT_ALLOCATION_FAILURE;
    }

    state_count = (size_t)k;
    counts = calloc(state_count, sizeof(*counts));
    if (counts == NULL) {
        return COUNT_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        uint64_t value = array[i];

        if (value == 0U) {
            uint64_t total = 0;

            for (size_t product = 0; product < state_count; ++product) {
                if (!checked_add(&total, counts[product])) {
                    free(counts);
                    return COUNT_OVERFLOW;
                }
            }

            if (!checked_add(&counts[0], total) ||
                !checked_add(&counts[0], 1U)) {
                free(counts);
                return COUNT_OVERFLOW;
            }
        } else if (value == 1U) {
            for (size_t product = 0; product < state_count; ++product) {
                if (!checked_add(&counts[product], counts[product])) {
                    free(counts);
                    return COUNT_OVERFLOW;
                }
            }

            if (value < k && !checked_add(&counts[1], 1U)) {
                free(counts);
                return COUNT_OVERFLOW;
            }
        } else {
            uint64_t maximum_source = (k - 1U) / value;
            size_t source = (size_t)maximum_source;

            for (;;) {
                size_t destination = (size_t)((uint64_t)source * value);

                if (!checked_add(&counts[destination], counts[source])) {
                    free(counts);
                    return COUNT_OVERFLOW;
                }

                if (source == 0U) {
                    break;
                }

                --source;
            }

            if (value < k &&
                !checked_add(&counts[(size_t)value], 1U)) {
                free(counts);
                return COUNT_OVERFLOW;
            }
        }
    }

    for (size_t product = 0; product < state_count; ++product) {
        if (!checked_add(result, counts[product])) {
            free(counts);
            *result = 0;
            return COUNT_OVERFLOW;
        }
    }

    free(counts);
    return COUNT_SUCCESS;
}

int main(void)
{
    const uint64_t array[] = {1U, 2U, 3U, 4U};
    const uint64_t k = 10U;
    uint64_t result;
    CountStatus status;

    status = count_subsequences_product_less_than_k(
        array,
        sizeof(array) / sizeof(array[0]),
        k,
        &result
    );

    if (status != COUNT_SUCCESS) {
        fprintf(stderr, "Unable to count subsequences\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}