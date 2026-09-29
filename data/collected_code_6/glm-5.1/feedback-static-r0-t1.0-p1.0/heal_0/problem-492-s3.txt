#include <stdio.h>
#include <stdlib.h>

int binary_search(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    size_t left = 0;
    size_t right = size - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return (int)mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
            if (mid == right) {
                break;
            }
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }

    return -1;
}

int main(void) {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int target = 12;
    int result = binary_search(arr, size, target);

    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    target = 5;
    result = binary_search(arr, size, target);

    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    return 0;
}