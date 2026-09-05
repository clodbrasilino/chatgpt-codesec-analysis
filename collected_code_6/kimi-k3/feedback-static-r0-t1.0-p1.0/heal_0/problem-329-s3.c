#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int count_negatives(const int *arr, size_t size, int *count)
{
    size_t i;
    int negative_count = 0;

    if (arr == NULL || count == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            negative_count++;
        }
    }

    *count = negative_count;
    return 0;
}

int main(void)
{
    int numbers[] = {1, -3, 5, -7, 9, -2, 0, 4, -6};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int negative_count = 0;
    int result;

    result = count_negatives(numbers, size, &negative_count);

    if (result != 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return 1;
    }

    printf("Number of negative numbers: %d\n", negative_count);

    return 0;
}