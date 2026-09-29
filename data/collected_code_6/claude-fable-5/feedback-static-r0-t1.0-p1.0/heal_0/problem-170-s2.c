#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_range(const int *list, size_t size, size_t start, size_t end, long long *result)
{
    if (list == NULL || result == NULL) {
        return -1;
    }
    if (size == 0 || start > end || end >= size) {
        return -1;
    }

    long long sum = 0;
    for (size_t i = start; i <= end; i++) {
        if (list[i] > 0 && sum > LLONG_MAX - list[i]) {
            return -1;
        }
        if (list[i] < 0 && sum < LLONG_MIN - list[i]) {
            return -1;
        }
        sum += list[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    int numbers[] = { 2, 1, 5, 6, 8, 3, 4, 9, 10, 11, 8, 12 };
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t start = 8;
    size_t end = 10;
    long long result = 0;

    if (sum_range(numbers, size, start, end, &result) != 0) {
        fprintf(stderr, "Error: invalid input or overflow detected\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum of elements from index %zu to %zu is %lld\n",
               start, end, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}