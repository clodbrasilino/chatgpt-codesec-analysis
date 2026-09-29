#include <stdio.h>
#include <stdbool.h>

int find_first_position(const int *arr, int arr_size, int target) {
    int left = 0;
    int right = arr_size - 1;
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
    int arr[] = {1, 2, 4, 4, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int target = 4;
    int position = find_first_position(arr, arr_size, target);
    if (position != -1) {
        printf("First occurrence of %d is at index: %d\n", target, position);
    } else {
        printf("%d not found in the array.\n", target);
    }
    return 0;
}