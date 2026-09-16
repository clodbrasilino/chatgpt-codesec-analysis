#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int sum_three_lowest_positive(const int numbers[], size_t count, long long *sum)
{
    int lowest = INT_MAX;
    int second = INT_MAX;
    int third = INT_MAX;
    size_t positive_count = 0;

    if (numbers == NULL || sum == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        int value = numbers[i];

        if (value <= 0) {
            continue;
        }

        ++positive_count;

        if (value < lowest) {
            third = second;
            second = lowest;
            lowest = value;
        } else if (value < second) {
            third = second;
            second = value;
        } else if (value < third) {
            third = value;
        }
    }

    if (positive_count < 3) {
        return 0;
    }

    *sum = (long long)lowest + second + third;
    return 1;
}

int main(void)
{
    const int numbers[] = {19, 5, 42, 2, 77, -3, 8, 1};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long sum = 0;

    if (!sum_three_lowest_positive(numbers, count, &sum)) {
        fputs("At least three positive numbers are required.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", sum) < 0) {
        return 1;
    }

    return 0;
}