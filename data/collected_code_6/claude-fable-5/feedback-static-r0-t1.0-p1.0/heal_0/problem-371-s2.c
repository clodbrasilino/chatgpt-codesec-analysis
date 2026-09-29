#include <stdio.h>
#include <stdlib.h>

int find_smallest_missing(const int *arr, size_t size)
{
    if (arr == NULL || size == 0) {
        return 0;
    }

    size_t low = 0;
    size_t high = size - 1;

    if (arr[0] != 0) {
        return 0;
    }

    if (arr[high] == (int)high) {
        return (int)size;
    }

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] == (int)mid) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return (int)low;
}

int main(void)
{
    int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 10};
    int arr2[] = {0, 1, 2, 6, 9, 11, 15};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {0, 1, 2, 3};

    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t n4 = sizeof(arr4) / sizeof(arr4[0]);

    if (printf("Smallest missing: %d\n", find_smallest_missing(arr1, n1)) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Smallest missing: %d\n", find_smallest_missing(arr2, n2)) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Smallest missing: %d\n", find_smallest_missing(arr3, n3)) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Smallest missing: %d\n", find_smallest_missing(arr4, n4)) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Smallest missing: %d\n", find_smallest_missing(NULL, 0)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}