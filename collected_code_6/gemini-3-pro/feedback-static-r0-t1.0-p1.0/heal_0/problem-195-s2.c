#include <stdio.h>
#include <stdlib.h>

int find_first_position(const int *arr, int size, int target) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int left = 0;
    int right = size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main() {
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;

    int position = find_first_position(arr, size, target);

    if (position != -1) {
        printf("First position of %d is %d\n", target, position);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    target = 5;
    position = find_first_position(arr, size, target);

    if (position != -1) {
        printf("First position of %d is %d\n", target, position);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    target = 7;
    position = find_first_position(arr, size, target);

    if (position != -1) {
        printf("First position of %d is %d\n", target, position);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    return 0;
}