#include <stdio.h>
#include <stdlib.h>

int find_smallest_missing(const int *arr, size_t n)
{
    size_t low;
    size_t high;

    if (arr == NULL || n == 0U) {
        return 0;
    }

    low = 0U;
    high = n - 1U;

    if (arr[0] != 0) {
        return 0;
    }

    if (arr[high] == (int)high) {
        return (int)n;
    }

    while (low < high) {
        const size_t mid = low + ((high - low) / 2U);
        if (arr[mid] == (int)mid) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    return (int)low;
}

int main(void)
{
    int arr1[] = {0, 1, 2, 3, 5, 6, 7};
    int arr2[] = {1, 2, 3, 4};
    int arr3[] = {0, 1, 2, 3, 4};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result;

    result = find_smallest_missing(arr1, n1);
    if (printf("Smallest missing element: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    result = find_smallest_missing(arr2, n2);
    if (printf("Smallest missing element: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    result = find_smallest_missing(arr3, n3);
    if (printf("Smallest missing element: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}