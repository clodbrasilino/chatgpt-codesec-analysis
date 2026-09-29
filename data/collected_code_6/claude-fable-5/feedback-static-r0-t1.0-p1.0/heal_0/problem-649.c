#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_range(const int *list, size_t length, size_t start, size_t end, long long *result)
{
    if (list == NULL || result == NULL) {
        return -1;
    }
    if (length == 0 || start > end || end >= length) {
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
    int numbers[] = {3, 8, 12, 5, 7, 2, 9, 14};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    size_t start = 2;
    size_t end = 5;
    long long total = 0;

    if (sum_range(numbers, length, start, end, &total) != 0) {
        fprintf(stderr, "Error: invalid input or overflow detected\n");
        return EXIT_FAILURE;
    }

    printf("Sum of elements from index %zu to %zu is %lld\n", start, end, total);

    return EXIT_SUCCESS;
}