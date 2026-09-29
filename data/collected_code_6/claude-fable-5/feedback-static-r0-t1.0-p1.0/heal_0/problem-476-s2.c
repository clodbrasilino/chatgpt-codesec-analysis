#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_min_max(const int *arr, size_t len, long long *result)
{
    size_t i;
    int min_val;
    int max_val;

    if (arr == NULL || result == NULL || len == 0U) {
        return -1;
    }

    min_val = arr[0];
    max_val = arr[0];

    for (i = 1U; i < len; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    *result = (long long)min_val + (long long)max_val;
    return 0;
}

int main(void)
{
    int numbers[] = { 34, -7, 23, 32, 5, 62, -14, 0 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long sum = 0;

    if (sum_min_max(numbers, count, &sum) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum of largest and smallest: %lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}