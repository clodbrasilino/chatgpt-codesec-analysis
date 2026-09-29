#include <stdio.h>
#include <stdlib.h>

static int sum_positive_numbers(const int numbers[], size_t count, long long *result)
{
    size_t i;
    long long sum = 0;

    if (numbers == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (numbers[i] > 0) {
            sum += numbers[i];
        }
    }

    *result = sum;
    return 0;
}

int main(void)
{
    int numbers[] = {-5, 10, 15, -3, 20, 0};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long sum;

    if (sum_positive_numbers(numbers, count, &sum) != 0) {
        fputs("Failed to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}