#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_negative_numbers(const int *numbers, size_t count, long long *result)
{
    size_t i;
    long long sum = 0;

    if (numbers == NULL || result == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }

    *result = sum;
    return EXIT_SUCCESS;
}

int main(void)
{
    const int numbers[] = {12, -4, 7, -9, 0, -3, 15};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long sum = 0;

    if (sum_negative_numbers(numbers, count, &sum) != EXIT_SUCCESS) {
        fputs("Failed to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum of negative numbers: %lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}