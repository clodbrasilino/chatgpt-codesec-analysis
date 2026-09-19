#include <stdio.h>
#include <stdlib.h>

int find_missing(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    if (arr[0] != 0) {
        return 0;
    }

    size_t low = 0;
    size_t high = size - 1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == (int)mid) {
            low = mid + 1;
        } else {
            if (mid == 0 || arr[mid - 1] == (int)(mid - 1)) {
                return (int)mid;
            }
            high = mid - 1;
        }
    }

    return (int)size;
}

int main(void) {
    int arr1[] = {0, 1, 2, 4, 5, 6};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int missing1 = find_missing(arr1, size1);
    printf("%d\n", missing1);

    int arr2[] = {1, 2, 3, 4, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int missing2 = find_missing(arr2, size2);
    printf("%d\n", missing2);

    int arr3[] = {0, 1, 2, 3, 4};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int missing3 = find_missing(arr3, size3);
    printf("%d\n", missing3);

    const int *arr4 = NULL;
    size_t size4 = 0;
    int missing4 = find_missing(arr4, size4);
    printf("%d\n", missing4);

    return 0;
}