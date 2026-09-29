#include <stdio.h>
#include <stdlib.h>

size_t frequency_of_smallest(const int *arr, size_t size)
{
    size_t count;
    size_t i;
    int min;

    if (arr == NULL || size == 0U) {
        return 0U;
    }

    min = arr[0];
    count = 1U;

    for (i = 1U; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
            count = 1U;
        } else if (arr[i] == min) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int data[] = { 5, 2, 8, 2, 9, 2, 7 };
    size_t size = sizeof(data) / sizeof(data[0]);
    size_t result;

    result = frequency_of_smallest(data, size);

    if (result == 0U) {
        if (printf("Array is empty or invalid\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Frequency of smallest value: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}