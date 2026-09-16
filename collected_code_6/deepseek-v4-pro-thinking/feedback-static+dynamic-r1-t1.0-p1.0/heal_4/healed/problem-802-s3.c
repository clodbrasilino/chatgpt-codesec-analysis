#include <stdio.h>
#include <stddef.h>

int countRotations(const int arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            if (arr[low] < arr[high]) {
                high = low;
            } else {
                if (arr[high - 1] > arr[high]) {
                    low = high;
                    break;
                }
                high--;
            }
        }
    }

    return (int)((n - low) % n);
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", countRotations(arr, n));

    return 0;
}