#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_subarray_products(const int64_t *array, size_t length,
                                    int64_t *result)
{
    int64_t ending_sum = 0;
    int64_t total_sum = 0;

    if (array == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int64_t product_sum;

        if (__builtin_mul_overflow(array[i], ending_sum, &product_sum) ||
            __builtin_add_overflow(array[i], product_sum, &ending_sum) ||
            __builtin_add_overflow(total_sum, ending_sum, &total_sum)) {
            return 0;
        }
    }

    *result = total_sum;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t result;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!sum_of_subarray_products(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}