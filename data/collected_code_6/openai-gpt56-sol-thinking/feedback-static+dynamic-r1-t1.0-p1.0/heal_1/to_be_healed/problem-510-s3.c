#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    COUNT_SUCCESS = 0,
    COUNT_INVALID_ARGUMENT,
    COUNT_MEMORY_ERROR,
    COUNT_RANGE_ERROR,
    COUNT_OVERFLOW
} CountStatus;

CountStatus count_subsequences_product_less_than_k(
    const uint64_t *values,
    size_t length,
    uint64_t k,
    uint64_t *result)
{
    uint64_t *current;
    uint64_t *next;
    uint64_t *temporary;
    size_t state_count;
    size_t i;
    size_t product;
    uint64_t total;

    if (result == NULL || (values == NULL && length != 0U)) {
        return COUNT_INVALID_ARGUMENT;
    }

    *result = 0U;

    if (length == 0U || k == 0U) {
        return COUNT_SUCCESS;
    }

    if (k > (uint64_t)SIZE_MAX) {
        return COUNT_RANGE_ERROR;
    }

    state_count = (size_t)k;

    if (state_count > SIZE_MAX / sizeof(*current)) {
        return COUNT_RANGE_ERROR;
    }

    current = calloc(state_count, sizeof(*current));
    if (current == NULL) {
        return COUNT_MEMORY_ERROR;
    }

    next = calloc(state_count, sizeof(*next));
    if (next == NULL) {
        free(current);
        return COUNT_MEMORY_ERROR;
    }

    for (i = 0U; i < length; ++i) {
        uint64_t value = values[i];

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(next, current, state_count * sizeof(*next));

        if (value < k) {
            size_t index = (size_t)value;

            if (next[index] == UINT64_MAX) {
                free(next);
                free(current);
                return COUNT_OVERFLOW;
            }

            ++next[index];
        }

        for (product = 0U; product < state_count; ++product) {
            size_t target;

            if (current[product] == 0U) {
                continue;
            }

            if (value != 0U && (uint64_t)product > (k - 1U) / value) {
                continue;
            }

            target = value == 0U
                ? 0U
                : (size_t)((uint64_t)product * value);

            if (UINT64_MAX - next[target] < current[product]) {
                free(next);
                free(current);
                return COUNT_OVERFLOW;
            }

            next[target] += current[product];
        }

        temporary = current;
        current = next;
        next = temporary;
    }

    total = 0U;

    for (product = 0U; product < state_count; ++product) {
        if (UINT64_MAX - total < current[product]) {
            free(next);
            free(current);
            return COUNT_OVERFLOW;
        }

        total += current[product];
    }

    free(next);
    free(current);
    *result = total;

    return COUNT_SUCCESS;
}

int main(void)
{
    uint64_t *values = NULL;
    uint64_t k;
    uint64_t result;
    size_t length;
    size_t i;
    CountStatus status;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%zu %" SCNu64, &length, &k) != 2) {
        return EXIT_FAILURE;
    }

    if (length > 0U) {
        if (length > SIZE_MAX / sizeof(*values)) {
            return EXIT_FAILURE;
        }

        values = malloc(length * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNu64, &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = count_subsequences_product_less_than_k(
        values,
        length,
        k,
        &result);

    free(values);

    if (status != COUNT_SUCCESS) {
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}