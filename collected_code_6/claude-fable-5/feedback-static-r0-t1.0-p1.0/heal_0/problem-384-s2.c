#include <stdio.h>
#include <stdlib.h>

int frequency_of_smallest(const int *arr, size_t size, int *result)
{
    size_t i;
    int min_val;
    int count;

    if (arr == NULL || size == 0 || result == NULL) {
        return -1;
    }

    min_val = arr[0];
    count = 1;

    for (i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            count = 1;
        } else if (arr[i] == min_val) {
            count++;
        }
    }

    *result = count;
    return 0;
}

int main(void)
{
    int arr[] = { 3, 1, 4, 1, 5, 9, 2, 6, 1, 3 };
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int freq = 0;

    if (frequency_of_smallest(arr, size, &freq) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Frequency of smallest value: %d\n", freq) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}