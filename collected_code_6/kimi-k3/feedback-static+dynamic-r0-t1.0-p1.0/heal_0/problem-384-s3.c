#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_smallest_frequency(const int *arr, size_t size, int *frequency) {
    if (arr == NULL || frequency == NULL || size == 0) {
        return -1;
    }

    int min = arr[0];
    size_t i;

    for (i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    int count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == min) {
            count++;
        }
    }

    *frequency = count;
    return 0;
}

int main(void) {
    int arr[] = {4, 2, 8, 2, 5, 2, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int frequency = 0;

    if (find_smallest_frequency(arr, size, &frequency) == 0) {
        printf("Frequency of the smallest value: %d\n", frequency);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}