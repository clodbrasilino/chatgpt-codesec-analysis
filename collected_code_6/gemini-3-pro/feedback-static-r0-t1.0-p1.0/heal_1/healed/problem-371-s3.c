#include <stdio.h>
#include <stdlib.h>

int findSmallestMissingInterval(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    int left = 0;
    int right = size - 1;

    if (arr[0] != 0) {
        return 0;
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

int main(void) {
    int arr1[] = {0, 1, 2, 3, 5, 6};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", findSmallestMissingInterval(arr1, size1));

    int arr2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", findSmallestMissingInterval(arr2, size2));

    int arr3[] = {0, 1, 2, 3, 4};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", findSmallestMissingInterval(arr3, size3));

    return 0;
}