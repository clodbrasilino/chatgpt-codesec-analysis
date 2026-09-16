#include <stdio.h>
#include <stddef.h>

static int sum_negative_numbers(const int numbers[], size_t count, long long *sum)
{
    size_t i;
    long long total = 0;

    if (numbers == NULL || sum == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (numbers[i] < 0) {
            total += numbers[i];
        }
    }

    *sum = total;
    return 0;
}

int main(void)
{
    const int numbers[] = {12, -7, 4, -15, 0, -3, 9};
    const size_t count = sizeof numbers / sizeof numbers[0];
    long long sum = 0;

    if (sum_negative_numbers(numbers, count, &sum) != 0) {
        (void)fprintf(stderr, "Failed to calculate the sum.\n");
        return 1;
    }

    if (printf("%lld\n", sum) < 0) {
        return 1;
    }

    return 0;
}