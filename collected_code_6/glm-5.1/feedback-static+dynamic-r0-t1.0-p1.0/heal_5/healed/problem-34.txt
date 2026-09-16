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
    int arr0[] = {0, 1, 2, 4, 5, 6};
    int missing0 = find_missing(arr0, sizeof(arr0) / sizeof(arr0[0]));
    printf("%d\n", missing0);

    int arr1[] = {1, 2, 3, 4, 5};
    int missing1 = find_missing(arr1, sizeof(arr1) / sizeof(arr1[0]));
    printf("%d\n", missing1);

    int arr2[] = {0, 1, 2, 3, 4};
    int missing2 = find_missing(arr2, sizeof(arr2) / sizeof(arr2[0]));
    printf("%d\n", missing2);

    int missing3 = find_missing(NULL, 0);
    printf("%d\n", missing3);

    return 0;
}