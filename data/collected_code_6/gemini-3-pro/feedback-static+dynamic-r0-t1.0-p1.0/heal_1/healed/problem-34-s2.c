#include <stdio.h>
#include <stdlib.h>

int findMissing(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] != mid + 1 && (mid == 0 || arr[mid - 1] == mid)) {
            return mid + 1;
        }

        if (arr[mid] == mid + 1) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return size + 1;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 6, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    int missingNumber = findMissing(arr, size);

    if (missingNumber != -1) {
        printf("Missing number: %d\n", missingNumber);
    } else {
        printf("Invalid input.\n");
    }

    return EXIT_SUCCESS;
}