#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int sum_negative_numbers(const long long numbers[], size_t count,
                                long long *result)
{
    long long sum = 0;

    if (numbers == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] < 0) {
            if (sum < LLONG_MIN - numbers[i]) {
                return -1;
            }
            sum += numbers[i];
        }
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t count = 0;
    long long *numbers = NULL;
    long long sum = 0;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid number count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*numbers)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%lld", &numbers[i]) != 1) {
            fputs("Invalid number.\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (sum_negative_numbers(numbers, count, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        free(numbers);
        return EXIT_FAILURE;
    }

    free(numbers);
    return EXIT_SUCCESS;
}