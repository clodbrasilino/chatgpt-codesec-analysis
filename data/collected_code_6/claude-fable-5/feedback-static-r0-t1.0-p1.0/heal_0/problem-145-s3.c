#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_difference(const int *arr, size_t size, int *result)
{
    size_t i;
    int min_val;
    int max_val;

    if (arr == NULL || result == NULL || size < 2U) {
        return -1;
    }

    min_val = arr[0];
    max_val = arr[0];

    for (i = 1U; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if ((max_val > 0) && (min_val < 0) && (max_val > (INT_MAX + min_val))) {
        return -1;
    }

    *result = max_val - min_val;
    return 0;
}

int main(void)
{
    int numbers[] = { 3, 10, 6, 1, 15, 8, 2 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int diff = 0;

    if (max_difference(numbers, count, &diff) != 0) {
        (void)fprintf(stderr, "Error: could not compute maximum difference\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum difference: %d\n", diff) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}