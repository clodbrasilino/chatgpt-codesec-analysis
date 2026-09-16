#include <stdio.h>
#include <stdlib.h>

int first_occurrence(const int arr[], int size, int target) {
    int left = 0, right = size - 1;
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

int main(void) {
    int arr[] = {1, 2, 3, 3, 3, 5, 6, 7, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 3;

    int index = first_occurrence(arr, size, target);

    if (index != -1) {
        printf("First occurrence of %d is at index %d\n", target, index);
    } else {
        printf("%d not found in array\n", target);
    }

    return 0;
}