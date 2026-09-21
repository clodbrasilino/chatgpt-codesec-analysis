#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

static int add_i64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int mul_i64_u64(int64_t a, uint64_t b, int64_t *result)
{
    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }

    if (a > 0) {
        if (b > (uint64_t)INT64_MAX / (uint64_t)a) {
            return 0;
        }
    } else {
        uint64_t magnitude = (uint64_t)(-(a + 1)) + 1;

        if (b > ((uint64_t)INT64_MAX + UINT64_C(1)) / magnitude) {
            return 0;
        }
    }

    if (b > (uint64_t)INT64_MAX) {
        if (a != -1 || b != (uint64_t)INT64_MAX + UINT64_C(1)) {
            return 0;
        }

        *result = INT64_MIN;
        return 1;
    }

    *result = a * (int64_t)b;
    return 1;
}

static int max_contiguous_sum_repeated(const int64_t *array,
                                       size_t length,
                                       uint64_t repetitions,
                                       int64_t *result)
{
    int64_t total = 0;
    int64_t prefix = 0;
    int64_t max_prefix = array[0];
    int64_t suffix = 0;
    int64_t max_suffix = array[length - 1];
    int64_t current = array[0];
    int64_t best = array[0];

    for (size_t i = 0; i < length; ++i) {
        if (!add_i64(total, array[i], &total) ||
            !add_i64(prefix, array[i], &prefix)) {
            return 0;
        }

        if (prefix > max_prefix) {
            max_prefix = prefix;
        }

        if (i > 0) {
            if (current > 0) {
                if (!add_i64(current, array[i], &current)) {
                    return 0;
                }
            } else {
                current = array[i];
            }

            if (current > best) {
                best = current;
            }
        }

        if (!add_i64(suffix, array[length - 1 - i], &suffix)) {
            return 0;
        }

        if (suffix > max_suffix) {
            max_suffix = suffix;
        }
    }

    if (repetitions == 1) {
        *result = best;
        return 1;
    }

    int64_t combined;

    if (!add_i64(max_suffix, max_prefix, &combined)) {
        return 0;
    }

    if (total > 0 && repetitions > 2) {
        int64_t middle;

        if (!mul_i64_u64(total, repetitions - 2, &middle) ||
            !add_i64(combined, middle, &combined)) {
            return 0;
        }
    }

    *result = combined > best ? combined : best;
    return 1;
}

int main(void)
{
    size_t length;
    uint64_t repetitions;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%zu %" SCNu64, &length, &repetitions) != 2 ||
        length == 0 ||
        repetitions == 0) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));

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

    int64_t result;

    if (!max_contiguous_sum_repeated(array, length, repetitions, &result)) {
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