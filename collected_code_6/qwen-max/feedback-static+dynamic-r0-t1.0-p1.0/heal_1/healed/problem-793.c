#include <stdio.h>
#include <stdlib.h>

int find_last_position(const int *array, int length, int target) {
    if (length <= 0) return -1;
    int left = 0, right = length - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == target) {
            result = mid;
            left = mid + 1;
        } else if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 4, 4, 5, 6, 6, 6, 7, 8};
    int length = sizeof(arr) / sizeof(arr[0]);
    int num = 6;
    int pos = find_last_position(arr, length, num);
    if (pos != -1) {
        printf("Last position of %d is: %d\n", num, pos);
    } else {
        printf("%d not found in the array.\n", num);
    }
    return 0;
}