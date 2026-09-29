#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int low = 0;
    int high = size - 1;
    int start = arr[0];

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == mid + start) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (low >= size) {
        return -1;
    }

    return low + start;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 7, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int missing1 = findMissingNumber(arr1, size1);
    if (missing1 != -1) {
        printf("Missing number: %d\n", missing1);
    } else {
        printf("Invalid input or no missing number\n");
    }

    int arr2[] = {10, 11, 12, 14, 15};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int missing2 = findMissingNumber(arr2, size2);
    if (missing2 != -1) {
        printf("Missing number: %d\n", missing2);
    } else {
        printf("Invalid input or no missing number\n");
    }

    int arr3[] = {2, 4, 6, 8, 12};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int missing3 = findMissingNumber(arr3, size3);
    if (missing3 != -1) {
        printf("Missing number: %d\n", missing3);
    } else {
        printf("Invalid input or no missing number\n");
    }

    int arr4[] = {1, 2, 3, 4, 5};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int missing4 = findMissingNumber(arr4, size4);
    if (missing4 != -1) {
        printf("Missing number: %d\n", missing4);
    } else {
        printf("Invalid input or no missing number\n");
    }

    int missing5 = findMissingNumber(NULL, 0);
    printf("Invalid input or no missing number\n");

    return EXIT_SUCCESS;
}