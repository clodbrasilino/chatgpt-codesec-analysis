#include <stdio.h>
#include <stdlib.h>

int findSmallestMissingElement(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    size_t left = 0;
    size_t right = size - 1;

    if (arr[0] != 0) {
        return 0;
    }

    if (arr[right] == (int)right) {
        return (int)(size);
    }

    while (left <= right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] != (int)mid) {
            if (mid == 0 || arr[mid - 1] == (int)(mid - 1)) {
                return (int)mid;
            }
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return (int)size;
}

int main(void) {
    int arr1[] = {0, 1, 2, 3, 5, 6};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {1, 2, 3, 4, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int arr3[] = {0, 1, 2, 3, 4};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("%d\n", findSmallestMissingElement(arr1, size1));
    printf("%d\n", findSmallestMissingElement(arr2, size2));
    printf("%d\n", findSmallestMissingElement(arr3, size3));

    return EXIT_SUCCESS;
}