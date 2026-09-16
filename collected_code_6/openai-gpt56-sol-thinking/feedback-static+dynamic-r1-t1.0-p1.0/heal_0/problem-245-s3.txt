#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool checked_add(long long a, long long b, long long *result)
{
    if ((b > 0 && a > LLONG_MAX - b) ||
        (b < 0 && a < LLONG_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool checked_subtract(long long a, long long b, long long *result)
{
    if ((b > 0 && a < LLONG_MIN + b) ||
        (b < 0 && a > LLONG_MAX + b)) {
        return false;
    }

    *result = a - b;
    return true;
}

bool maximum_sum_bitonic_subsequence(const long long *array,
                                     size_t length,
                                     long long *result)
{
    long long *increasing;
    long long *decreasing;
    long long maximum;

    if (array == NULL || result == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*increasing)) {
        return false;
    }

    increasing = malloc(length * sizeof(*increasing));
    if (increasing == NULL) {
        return false;
    }

    decreasing = malloc(length * sizeof(*decreasing));
    if (decreasing == NULL) {
        free(increasing);
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        increasing[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            long long candidate;

            if (array[j] < array[i] && increasing[j] > 0) {
                if (!checked_add(increasing[j], array[i], &candidate)) {
                    free(decreasing);
                    free(increasing);
                    return false;
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
            long long candidate;

            if (array[j] < array[i] && decreasing[j] > 0) {
                if (!checked_add(array[i], decreasing[j], &candidate)) {
                    free(decreasing);
                    free(increasing);
                    return false;
                }

                if (candidate > decreasing[i]) {
                    decreasing[i] = candidate;
                }
            }
        }
    }

    maximum = array[0];

    for (size_t i = 0; i < length; ++i) {
        long long decreasing_tail;
        long long candidate;

        if (!checked_subtract(decreasing[i], array[i], &decreasing_tail) ||
            !checked_add(increasing[i], decreasing_tail, &candidate)) {
            free(decreasing);
            free(increasing);
            return false;
        }

        if (candidate > maximum) {
            maximum = candidate;
        }
    }

    free(decreasing);
    free(increasing);
    *result = maximum;
    return true;
}

int main(void)
{
    size_t length;
    long long *array;
    long long result;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%lld", &array[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_sum_bitonic_subsequence(array, length, &result)) {
        fputs("Unable to compute result\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    free(array);
    return EXIT_SUCCESS;
}