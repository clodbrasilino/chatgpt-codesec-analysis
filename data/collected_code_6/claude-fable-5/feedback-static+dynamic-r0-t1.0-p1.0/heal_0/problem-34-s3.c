#include <stdio.h>
#include <stdlib.h>

int find_missing_number(const int *arr, size_t n, int *missing)
{
    size_t low;
    size_t high;
    size_t mid;

    if (arr == NULL || missing == NULL || n == 0U) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    if ((size_t)(arr[high] - arr[0]) == high) {
        return -1;
    }

    while (low < high) {
        mid = low + ((high - low) / 2U);
        if ((size_t)(arr[mid] - arr[0]) == mid) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    *missing = arr[0] + (int)low;
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 6, 7, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int missing = 0;
    int result;

    result = find_missing_number(arr, n, &missing);
    if (result == 0) {
        if (printf("Missing number: %d\n", missing) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No missing number found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}