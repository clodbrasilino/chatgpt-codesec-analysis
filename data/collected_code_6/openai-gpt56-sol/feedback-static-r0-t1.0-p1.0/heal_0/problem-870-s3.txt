#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int sum_positive(const int *numbers, size_t count, long long *sum)
{
    size_t i;
    long long total = 0;

    if ((numbers == NULL && count != 0U) || sum == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (numbers[i] > 0) {
            if (total > LLONG_MAX - numbers[i]) {
                return -1;
            }
            total += numbers[i];
        }
    }

    *sum = total;
    return 0;
}

int main(void)
{
    size_t count;
    int *numbers = NULL;
    long long sum;
    size_t i;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*numbers)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (sum_positive(numbers, count, &sum) != 0) {
        fputs("Unable to calculate sum\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        fputs("Output error\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }

    free(numbers);
    return EXIT_SUCCESS;
}