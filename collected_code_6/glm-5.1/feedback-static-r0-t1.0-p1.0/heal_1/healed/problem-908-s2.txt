#include <stdio.h>
#include <stdlib.h>

int find_fixed_point(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = size - 1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == (int)mid) {
            return (int)mid;
        } else if (arr[mid] < (int)mid) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }

    return -1;
}

int main(void) {
    int arr1[] = {-10, -5, 0, 3, 7};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_fixed_point(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {-10, -5, 3, 4, 7};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_fixed_point(arr2, size2);
    printf("%d\n", result2);

    int arr3[] = {0, 2, 5, 8, 17};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = find_fixed_point(arr3, size3);
    printf("%d\n", result3);

    int result4 = find_fixed_point(NULL, size1);
    printf("%d\n", result4);

    return 0;
}