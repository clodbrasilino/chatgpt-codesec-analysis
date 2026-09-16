#include <stdio.h>
#include <stdlib.h>

int find_missing_number(const int *arr, size_t n, int *missing)
{
    size_t low;
    size_t high;

    if (arr == NULL || missing == NULL || n == 0U) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    if (arr[0] != 1) {
        *missing = 1;
        return 0;
    }

    if (arr[high] == (int)(n)) {
        return -1;
    }

    while (low < high) {
        size_t mid = low + ((high - low) / 2U);
        if (arr[mid] == (int)(mid + 1U)) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    *missing = (int)(low + 1U);
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 6, 7, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int missing = 0;
    int result;

    result = find_missing_number(arr, n, &missing);
    if (result != 0) {
        if (fprintf(stderr, "No missing number found or invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Missing number: %d\n", missing) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}