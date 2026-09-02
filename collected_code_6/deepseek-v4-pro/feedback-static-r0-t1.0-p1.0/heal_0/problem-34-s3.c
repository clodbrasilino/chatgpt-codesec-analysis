#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(const int *arr, int size) {
    if (arr == NULL || size < 2) {
        return -1;
    }

    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] != mid + arr[0]) {
            if (mid == 0 || arr[mid - 1] == (mid - 1) + arr[0]) {
                return mid + arr[0];
            }
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int main(void) {
    int arr1[] = {1, 2, 3, 5, 6, 7, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int missing1 = findMissingNumber(arr1, size1);
    printf("Missing number: %d\n", missing1);

    int arr2[] = {10, 11, 12, 14, 15};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int missing2 = findMissingNumber(arr2, size2);
    printf("Missing number: %d\n", missing2);

    int arr3[] = {-3, -2, -1, 1, 2};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int missing3 = findMissingNumber(arr3, size3);
    printf("Missing number: %d\n", missing3);

    int arr4[] = {1, 2};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int missing4 = findMissingNumber(arr4, size4);
    printf("Missing number: %d\n", missing4);

    int *arr5 = NULL;
    int missing5 = findMissingNumber(arr5, 0);
    printf("Missing number: %d\n", missing5);

    return 0;
}