#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int find_peak_element(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    size_t left = 0;
    size_t right = size - 1;

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] > arr[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return arr[left];
}

int main(void) {
    int arr[] = {1, 2, 3, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int peak = find_peak_element(arr, size);
    if (peak != -1) {
        printf("Peak element is: %d\n", peak);
    } else {
        printf("Invalid array or empty array.\n");
    }

    int arr2[] = {1, 2, 1, 3, 5, 6, 4};
    size = sizeof(arr2) / sizeof(arr2[0]);

    peak = find_peak_element(arr2, size);
    if (peak != -1) {
        printf("Peak element is: %d\n", peak);
    } else {
        printf("Invalid array or empty array.\n");
    }

    return 0;
}