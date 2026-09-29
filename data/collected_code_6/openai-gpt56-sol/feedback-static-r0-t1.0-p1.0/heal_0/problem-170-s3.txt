#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_range(const int *list, size_t length, size_t start, size_t end,
                     long long *result)
{
    if (list == NULL || result == NULL || start > end || end >= length) {
        return -1;
    }

    long long sum = 0;

    for (size_t i = start; i <= end; ++i) {
        sum += list[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const int numbers[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    const size_t start = 1;
    const size_t end = 3;
    long long sum = 0;

    if (sum_range(numbers, length, start, end, &sum) != 0) {
        fputs("Invalid range or arguments.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum from index %zu to %zu: %lld\n", start, end, sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}