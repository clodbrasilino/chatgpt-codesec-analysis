#include <stdio.h>

int leftInsertionPoint(int arr[], int n, int key) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int main() {
    int arr[] = {1, 2, 4, 4, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 4;
    int index = leftInsertionPoint(arr, n, key);
    printf("Left insertion point for %d is at index %d\n", key, index);
    return 0;
}