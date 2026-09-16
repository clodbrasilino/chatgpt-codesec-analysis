#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>

static int checked_multiply(long long a, long long b, long long *result)
{
    if (result == NULL) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > LLONG_MAX / b) ||
            (b < 0 && b < LLONG_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < LLONG_MIN / b) ||
            (b < 0 && a < LLONG_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int maximum_increasing_subsequence_product(
    const long long *values,
    size_t count,
    long long *maximum)
{
    long long *largest = NULL;
    long long *smallest = NULL;
    long long answer;
    size_t i;
    size_t j;

    if (values == NULL || maximum == NULL || count == 0 ||
        count > SIZE_MAX / sizeof(*largest)) {
        return 0;
    }

    largest = malloc(count * sizeof(*largest));
    smallest = malloc(count * sizeof(*smallest));
    if (largest == NULL || smallest == NULL) {
        free(largest);
        free(smallest);
        return 0;
    }

    answer = values[0];

    for (i = 0; i < count; ++i) {
        largest[i] = values[i];
        smallest[i] = values[i];

        for (j = 0; j < i; ++j) {
            long long candidate;

            if (values[j] >= values[i]) {
                continue;
            }

            if (checked_multiply(largest[j], values[i], &candidate)) {
                if (candidate > largest[i]) {
                    largest[i] = candidate;
                }
                if (candidate < smallest[i]) {
                    smallest[i] = candidate;
                }
            }

            if (checked_multiply(smallest[j], values[i], &candidate)) {
                if (candidate > largest[i]) {
                    largest[i] = candidate;
                }
                if (candidate < smallest[i]) {
                    smallest[i] = candidate;
                }
            }
        }

        if (largest[i] > answer) {
            answer = largest[i];
        }
    }

    free(largest);
    free(smallest);
    *maximum = answer;
    return 1;
}

int main(void)
{
    size_t count;
    size_t i;
    long long *values = NULL;
    long long maximum;

    errno = 0;
    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%lld", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_increasing_subsequence_product(values, count, &maximum)) {
        fputs("Unable to compute the maximum product\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%lld\n", maximum);
    free(values);
    return EXIT_SUCCESS;
}