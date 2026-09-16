#include <stdio.h>
#include <stdlib.h>

int findCount(const int arr[], int n, int target) {
    int start = 0;
    int end = n - 1;
    int result = -1;

    if (arr == NULL || n <= 0) {
        return -1;
    }

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

    return result;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 2;

    int lastPosition = findCount(arr, n, target);

    printf("%d\n", lastPosition);

    return 0;
}