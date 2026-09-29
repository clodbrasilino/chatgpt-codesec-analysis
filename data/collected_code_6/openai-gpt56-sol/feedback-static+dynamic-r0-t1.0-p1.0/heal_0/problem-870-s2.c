#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_positive(const int *numbers, size_t count, long long *result)
{
    size_t i;
    long long sum = 0;

    if (result == NULL || (numbers == NULL && count != 0U)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (numbers[i] > 0) {
            sum += numbers[i];
        }
    }

    *result = sum;
    return EXIT_SUCCESS;
}

int main(void)
{
    const int numbers[] = {-8, 4, 12, -3, 7, 0, -5};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long sum;

    if (sum_positive(numbers, count, &sum) != EXIT_SUCCESS) {
        (void)fprintf(stderr, "Failed to calculate the sum.\n");
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}