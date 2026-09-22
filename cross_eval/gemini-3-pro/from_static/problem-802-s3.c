#include <stdio.h>
#include <stdlib.h>

int countRotations(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        if (arr[left] <= arr[right]) {
            return left;
        }

        int mid = left + (right - left) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        } else if (arr[mid] <= arr[right]) {
            right = mid - 1;
        } else if (arr[mid] >= arr[left]) {
            left = mid + 1;
        }
    }

    return 0;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    int rotations = countRotations(arr, n);

    if (rotations != -1) {
        printf("%d\n", rotations);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}