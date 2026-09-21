#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int sum_absolute_differences(int64_t *array, size_t length,
                                    uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t prefix_magnitude = 0;
    int prefix_negative = 0;

    if (array == NULL || result == NULL) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        uint64_t value;
        uint64_t product;
        uint64_t difference_sum;

        if (array[i] >= 0) {
            value = (uint64_t)array[i];

            if (i != 0 && value > UINT64_MAX / (uint64_t)i) {
                return -1;
            }

            product = value * (uint64_t)i;

            if (prefix_negative) {
                if (product > UINT64_MAX - prefix_magnitude) {
                    return -1;
                }
                difference_sum = product + prefix_magnitude;

                if (value >= prefix_magnitude) {
                    prefix_magnitude = value - prefix_magnitude;
                    prefix_negative = 0;
                } else {
                    prefix_magnitude -= value;
                }
            } else {
                if (product < prefix_magnitude) {
                    return -1;
                }
                difference_sum = product - prefix_magnitude;

                if (prefix_magnitude > UINT64_MAX - value) {
                    return -1;
                }
                prefix_magnitude += value;
            }
        } else {
            value = (uint64_t)(-(array[i] + INT64_C(1))) + UINT64_C(1);

            if (i != 0 && value > UINT64_MAX / (uint64_t)i) {
                return -1;
            }

            product = value * (uint64_t)i;

            if (prefix_negative) {
                if (product > UINT64_MAX - prefix_magnitude) {
                    return -1;
                }
                difference_sum = product + prefix_magnitude;

                if (prefix_magnitude > UINT64_MAX - value) {
                    return -1;
                }
                prefix_magnitude += value;
            } else {
                if (product < prefix_magnitude) {
                    return -1;
                }
                difference_sum = product - prefix_magnitude;

                if (value >= prefix_magnitude) {
                    prefix_magnitude = value - prefix_magnitude;
                    prefix_negative = prefix_magnitude != 0;
                } else {
                    prefix_magnitude -= value;
                }
            }
        }

        if (sum > UINT64_MAX - difference_sum) {
            return -1;
        }

        sum += difference_sum;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    uint64_t result;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_absolute_differences(array, length, &result) != 0) {
        fputs("Result exceeds the supported range\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);

    return EXIT_SUCCESS;
}