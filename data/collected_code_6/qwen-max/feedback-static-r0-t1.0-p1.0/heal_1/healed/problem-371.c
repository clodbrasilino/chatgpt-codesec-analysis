#include <stdio.h>
#include <stdlib.h>

int findSmallestMissing(const int *arr, int n) {
    if (n == 0 || arr[0] != 0) {
        return 0;
    }
    if (arr[n-1] == n - 1) {
        return n;
    }

    int low = 0, high = n - 1;
    while (high > low + 1) {
        int mid = (low + high) / 2;
        if (arr[mid] == mid) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return arr[low] + 1;
}

int main() {
    int arr[] = {0, 1, 2, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The smallest missing element is: %d\n", findSmallestMissing(arr, n));
    return 0;
}