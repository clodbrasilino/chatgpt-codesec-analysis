#include <stdio.h>
#include <stdlib.h>

long long min_swaps_to_sort_binary(const int *arr, size_t n)
{
    long long swaps = 0;
    long long ones_seen = 0;
    size_t i;

    if (arr == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] == 1) {
            ones_seen++;
        } else if (arr[i] == 0) {
            swaps += ones_seen;
        } else {
            return -1;
        }
    }

    return swaps;
}

int main(void)
{
    int arr1[] = {1, 0, 1, 0, 1};
    int arr2[] = {0, 0, 1, 0, 1, 0, 1, 1};
    int arr3[] = {1, 1, 1, 0, 0};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    long long result;

    result = min_swaps_to_sort_binary(arr1, n1);
    if (result < 0) {
        fprintf(stderr, "Invalid input array\n");
        return EXIT_FAILURE;
    }
    printf("Minimum swaps for array 1: %lld\n", result);

    result = min_swaps_to_sort_binary(arr2, n2);
    if (result < 0) {
        fprintf(stderr, "Invalid input array\n");
        return EXIT_FAILURE;
    }
    printf("Minimum swaps for array 2: %lld\n", result);

    result = min_swaps_to_sort_binary(arr3, n3);
    if (result < 0) {
        fprintf(stderr, "Invalid input array\n");
        return EXIT_FAILURE;
    }
    printf("Minimum swaps for array 3: %lld\n", result);

    return EXIT_SUCCESS;
}