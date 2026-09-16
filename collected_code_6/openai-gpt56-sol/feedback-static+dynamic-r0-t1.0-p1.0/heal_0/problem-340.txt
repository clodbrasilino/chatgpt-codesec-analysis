#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_three_lowest_positive(const long long *numbers,
                                     size_t count,
                                     long long *result)
{
    if (numbers == NULL || result == NULL) {
        return 0;
    }

    long long lowest[3] = {LLONG_MAX, LLONG_MAX, LLONG_MAX};
    size_t positive_count = 0;

    for (size_t i = 0; i < count; ++i) {
        const long long value = numbers[i];

        if (value <= 0) {
            continue;
        }

        ++positive_count;

        if (value < lowest[0]) {
            lowest[2] = lowest[1];
            lowest[1] = lowest[0];
            lowest[0] = value;
        } else if (value < lowest[1]) {
            lowest[2] = lowest[1];
            lowest[1] = value;
        } else if (value < lowest[2]) {
            lowest[2] = value;
        }
    }

    if (positive_count < 3) {
        return 0;
    }

    if (lowest[0] > LLONG_MAX - lowest[1]) {
        return 0;
    }

    const long long partial_sum = lowest[0] + lowest[1];

    if (partial_sum > LLONG_MAX - lowest[2]) {
        return 0;
    }

    *result = partial_sum + lowest[2];
    return 1;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count > SIZE_MAX / sizeof(long long)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    long long *numbers = NULL;

    if (count > 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%lld", &numbers[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    long long sum = 0;
    const int success = sum_three_lowest_positive(numbers, count, &sum);

    free(numbers);

    if (!success) {
        fputs("Unable to compute the sum\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}