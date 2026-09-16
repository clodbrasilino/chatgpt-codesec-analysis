#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_range(const int *numbers, size_t length, size_t start,
                     size_t end, long long *result)
{
    long long sum = 0;

    if (numbers == NULL || result == NULL || start > end || end >= length) {
        return -1;
    }

    for (size_t i = start; i <= end; ++i) {
        sum += numbers[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const int numbers[] = {10, 20, 30, 40, 50, 60};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    long long sum = 0;

    if (sum_range(numbers, length, 1, 4, &sum) != 0) {
        fputs("Invalid range or argument.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}