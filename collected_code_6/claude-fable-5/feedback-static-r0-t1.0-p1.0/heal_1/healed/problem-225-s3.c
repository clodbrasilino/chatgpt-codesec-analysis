#include <stdio.h>
#include <stdlib.h>

int find_min(const int *arr, size_t n, int *result)
{
    size_t low;
    size_t high;

    if (arr == NULL || n == 0U || result == NULL) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high) {
        size_t mid = low + ((high - low) / 2U);
        if (arr[mid] > arr[high]) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    *result = arr[low];
    return 0;
}

int main(void)
{
    int arr[] = {5, 6, 7, 1, 2, 3, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int minimum;

    if (find_min(arr, n, &minimum) != 0) {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum element: %d\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}