#include <stdio.h>

int findLastPosition(int *arr, int size, int target) {
    int low = 0;
    int high = size - 1;
    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 4, 4, 5, 6, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 4;
    int lastPos = findLastPosition(arr, size, target);
    if (lastPos != -1) {
        printf("The last position of %d is %d.\n", target, lastPos);
    } else {
        printf("%d is not found in the array.\n", target);
    }
    return 0;
}