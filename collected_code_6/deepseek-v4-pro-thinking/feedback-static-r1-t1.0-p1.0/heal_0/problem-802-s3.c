#include <stdio.h>
#include <stddef.h>

int countRotations(const int arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return (int)low;
        }

        size_t mid = low + (high - low) / 2;
        size_t next = (mid + 1) % n;
        size_t prev = (mid == 0) ? n - 1 : mid - 1;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return (int)mid;
        }

        if (arr[low] <= arr[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", countRotations(arr, n));

    return 0;
}