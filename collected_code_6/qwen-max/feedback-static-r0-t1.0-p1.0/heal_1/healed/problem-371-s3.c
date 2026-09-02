#include <stdio.h>
#include <stdlib.h>

int findSmallestMissing(const int *arr, int n) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == mid + 1) {
            low = mid + 1;
        } else {
            if (mid == 0 || arr[mid - 1] == mid) {
                return mid + 1;
            }
            high = mid - 1;
        }
    }
    return n + 1;
}

int main() {
    int arr[] = {1, 2, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findSmallestMissing(arr, n);
    if (result != n + 1) {
        printf("The smallest missing element is %d\n", result);
    } else {
        printf("No missing element in the array.\n");
    }
    return 0;
}