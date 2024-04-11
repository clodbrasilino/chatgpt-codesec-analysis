#include <stdio.h>

int findInsertionPoint(int arr[], int n, int key) {
    int start = 0;
    int end = n - 1;
    int mid;

    while (start <= end) {
        mid = start + (end - start) / 2;

        if (arr[mid] == key) {
            while (mid - 1 >= 0 && arr[mid - 1] == key) {
                mid--;
            }
            return mid;
        } else if (arr[mid] < key) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return start;
}

int main() {
    int arr[] = {1, 2, 4, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 4;

    int index = findInsertionPoint(arr, n, key);

    printf("The left insertion point for %d is at index %d\n", key, index);

    return 0;
}