#include <stdio.h>
#include <stdlib.h>

int find_last_position(int *arr, int size, int target) {
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
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;

    int pos = find_last_position(arr, size, target);

    if (pos != -1) {
        printf("Last position of %d is %d\n", target, pos);
    } else {
        printf("Element %d not found\n", target);
    }

    return 0;
}