#include <stdio.h>
#include <stdlib.h>

long long find_difference(const int *arr, size_t size)
{
    size_t i;
    int min_val;
    int max_val;

    if (arr == NULL || size == 0U) {
        fprintf(stderr, "Error: invalid array or size\n");
        exit(EXIT_FAILURE);
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

    return (long long)max_val - (long long)min_val;
}

int main(void)
{
    int numbers[] = { 34, -7, 89, 12, 0, -25, 56 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long diff;

    diff = find_difference(numbers, count);

    if (printf("Difference between largest and smallest: %lld\n", diff) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}