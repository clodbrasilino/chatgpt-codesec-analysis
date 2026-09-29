#include <stdio.h>
#include <stdlib.h>

int findSmallestMissing(const int *arr, int n) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > mid) {
            if (mid == 0 || arr[mid - 1] == mid - 1) {
                return mid;
            }
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return n;
}

int main() {
    int arr[] = {0, 1, 2, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findSmallestMissing(arr, n);
    printf("The smallest missing element is: %d\n", result);
    return 0;
}