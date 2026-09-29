#include <stdio.h>
#include <stdbool.h>

bool binary_search(const int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return true;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

int main() {
    const int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    bool result = binary_search(arr, size, target);

    if (result) {
        printf("Element found.\n");
    } else {
        printf("Element not found in the array.\n");
    }

    target = 2;
    result = binary_search(arr, size, target);
    if (result) {
        printf("Element found.\n");
    } else {
        printf("Element not found in the array.\n");
    }

    target = 16;
    result = binary_search(arr, size, target);
    if (result) {
        printf("Element found.\n");
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}