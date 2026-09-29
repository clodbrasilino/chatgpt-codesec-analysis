#include <stdio.h>
#include <stdlib.h>

int frequency_of_largest(const int *arr, size_t size, int *freq)
{
    size_t i;
    int max;
    int count;

    if (arr == NULL || size == 0 || freq == NULL) {
        return -1;
    }

    max = arr[0];
    count = 1;

    for (i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            count = 1;
        } else if (arr[i] == max) {
            count++;
        }
    }

    *freq = count;
    return 0;
}

int main(void)
{
    int arr[] = {3, 7, 2, 7, 5, 7, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int freq = 0;

    if (frequency_of_largest(arr, size, &freq) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Frequency of the largest value: %d\n", freq) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}