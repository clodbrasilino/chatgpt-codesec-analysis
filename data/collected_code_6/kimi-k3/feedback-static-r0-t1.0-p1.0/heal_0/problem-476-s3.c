#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int sum_largest_smallest(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int min = arr[0];
    int max = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return min + max;
}

int main(void) {
    int arr[] = {3, 5, 1, 9, 2, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_largest_smallest(arr, size);
    printf("Sum of largest and smallest: %d\n", result);

    return 0;
}