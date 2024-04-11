#include <stdio.h>

int findInsertionPoint(int arr[], int n, int target) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 6;
    int index = findInsertionPoint(arr, n, target);
    printf("The left insertion point for %d is at index %d\n", target, index);
    return 0;
}