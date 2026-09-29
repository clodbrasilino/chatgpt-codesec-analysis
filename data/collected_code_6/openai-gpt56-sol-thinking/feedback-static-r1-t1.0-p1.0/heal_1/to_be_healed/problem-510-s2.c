#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool count_subsequences_product_less_than_k(
    const uint64_t *array,
    size_t length,
    uint64_t k,
    uint64_t *result
) {
    uint64_t *counts = NULL;
    uint64_t *next_counts = NULL;
    size_t states;
    size_t i;
    size_t product;

    if (result == NULL || (array == NULL && length != 0)) {
        return false;
    }

    *result = 0;

    if (k == 0 || length == 0) {
        return true;
    }

    if (k > SIZE_MAX || (size_t)k > SIZE_MAX / sizeof(*counts)) {
        return false;
    }

    states = (size_t)k;
    counts = calloc(states, sizeof(*counts));
    next_counts = calloc(states, sizeof(*next_counts));

    if (counts == NULL || next_counts == NULL) {
        free(counts);
        free(next_counts);
        return false;
    }

    for (i = 0; i < length; ++i) {
        uint64_t value = array[i];

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(next_counts, counts, states * sizeof(*counts));

        if (value < k) {
            size_t index = (size_t)value;

            if (next_counts[index] == UINT64_MAX) {
                free(counts);
                free(next_counts);
                return false;
            }

            ++next_counts[index];
        }

        for (product = 0; product < states; ++product) {
            size_t new_product;

            if (counts[product] == 0) {
                continue;
            }

            if (value == 0) {
                new_product = 0;
            } else {
                if ((uint64_t)product > (k - 1) / value) {
                    continue;
                }

                new_product = (size_t)((uint64_t)product * value);
            }

            if (UINT64_MAX - next_counts[new_product] < counts[product]) {
                free(counts);
                free(next_counts);
                return false;
            }

            next_counts[new_product] += counts[product];
        }

        {
            uint64_t *temporary = counts;
            counts = next_counts;
            next_counts = temporary;
        }
    }

    for (product = 0; product < states; ++product) {
        if (UINT64_MAX - *result < counts[product]) {
            free(counts);
            free(next_counts);
            return false;
        }

        *result += counts[product];
    }

    free(counts);
    free(next_counts);
    return true;
}

int main(void) {
    uintmax_t input_length;
    uint64_t k;
    uint64_t *array = NULL;
    uint64_t result;
    size_t length;
    size_t i;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%ju %" SCNu64, &input_length, &k) != 2) {
        return EXIT_FAILURE;
    }

    if (input_length > SIZE_MAX) {
        return EXIT_FAILURE;
    }

    length = (size_t)input_length;

    if (length != 0) {
        if (length > SIZE_MAX / sizeof(*array)) {
            return EXIT_FAILURE;
        }

        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNu64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!count_subsequences_product_less_than_k(array, length, k, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}