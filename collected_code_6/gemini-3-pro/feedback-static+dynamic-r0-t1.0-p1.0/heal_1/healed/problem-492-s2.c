#include <stdio.h>
#include <stddef.h>

int binary_search(const int *arr, size_t size, int target);

int binary_search(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    size_t left = 0;
    size_t right = size - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return 1;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }

    return 0;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 13;

    int result = binary_search(arr, size, target);

    if (result) {
        printf("Element %d found in the array\n", target);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    return 0;
}