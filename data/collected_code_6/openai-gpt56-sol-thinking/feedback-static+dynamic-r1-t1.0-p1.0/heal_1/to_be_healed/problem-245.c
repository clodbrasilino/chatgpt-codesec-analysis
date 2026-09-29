#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static bool checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool checked_sub_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return false;
    }

    *result = a - b;
    return true;
}

bool max_sum_bitonic_subsequence(const int64_t *array, size_t length,
                                 int64_t *result)
{
    int64_t *increasing = NULL;
    int64_t *decreasing = NULL;
    int64_t best;
    bool success = false;

    if (result == NULL) {
        return false;
    }

    if (length == 0) {
        *result = 0;
        return true;
    }

    if (array == NULL || length > SIZE_MAX / sizeof(*increasing)) {
        return false;
    }

    increasing = malloc(length * sizeof(*increasing));
    if (increasing == NULL) {
        goto cleanup;
    }

    decreasing = malloc(length * sizeof(*decreasing));
    if (decreasing == NULL) {
        goto cleanup;
    }

    for (size_t i = 0; i < length; ++i) {
        increasing[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            int64_t candidate;

            if (array[j] < array[i]) {
                if (!checked_add_int64(increasing[j], array[i], &candidate)) {
                    goto cleanup;
                }

                if (candidate > increasing[i]) {
                    increasing[i] = candidate;
                }
            }
        }
    }

    for (size_t i = length; i-- > 0;) {
        decreasing[i] = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            int64_t candidate;

            if (array[j] < array[i]) {
                if (!checked_add_int64(array[i], decreasing[j], &candidate)) {
                    goto cleanup;
                }

                if (candidate > decreasing[i]) {
                    decreasing[i] = candidate;
                }
            }
        }
    }

    best = array[0];

    for (size_t i = 0; i < length; ++i) {
        int64_t decreasing_tail;
        int64_t candidate;

        if (!checked_sub_int64(decreasing[i], array[i], &decreasing_tail) ||
            !checked_add_int64(increasing[i], decreasing_tail, &candidate)) {
            goto cleanup;
        }

        if (candidate > best) {
            best = candidate;
        }
    }

    *result = best;
    success = true;

cleanup:
    free(decreasing);
    free(increasing);
    return success;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t result;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
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

    if (!max_sum_bitonic_subsequence(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}