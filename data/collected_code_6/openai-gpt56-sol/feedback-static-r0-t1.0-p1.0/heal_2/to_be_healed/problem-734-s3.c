#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_subarray_products(const int64_t *values, size_t count,
                                    int64_t *result)
{
    int64_t ending_sum = 0;
    int64_t total = 0;

    if (values == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t product;
        int64_t next_ending_sum;
        int64_t next_total;

        if (__builtin_mul_overflow(values[i], ending_sum, &product) ||
            __builtin_add_overflow(values[i], product, &next_ending_sum) ||
            __builtin_add_overflow(total, next_ending_sum, &next_total)) {
            return -1;
        }

        ending_sum = next_ending_sum;
        total = next_total;
    }

    *result = total;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values;
    int64_t result;

    if (scanf("%zu", &count) != 1 ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (sum_of_subarray_products(values, count, &result) != 0) {
        fputs("Arithmetic overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}