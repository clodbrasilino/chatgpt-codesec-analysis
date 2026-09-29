#include <stdio.h>

int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[mid] == target) {
            return mid;
        }

        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 12;

    int result = binarySearch(arr, size, target);

    if (result == -1) {
        printf("Element not found in array\n");
    } else {
        printf("Element found at index %d\n", result);
    }

    return 0;
}