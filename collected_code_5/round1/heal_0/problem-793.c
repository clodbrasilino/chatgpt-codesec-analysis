#include <stdio.h>

int find_last_position(int arr[], int n, int target) {
    int start = 0;
    int end = n - 1;
    int result = -1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            result = mid;
            start = mid + 1;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    if (result != -1) {
        return result;
    } else {
        printf("\nElement not found in the array.");
        return -1;
    }
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 2, 3};
    int len = sizeof(arr) / sizeof(arr[0]);
    int target = 2;

    int final_position = find_last_position(arr, len, target);

    if (final_position != -1) {
        printf("\nThe last position of the element in the sorted array is: %d", final_position);
    }

    return 0;
}