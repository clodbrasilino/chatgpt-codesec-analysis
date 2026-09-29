#include <stdio.h>
#include <stdlib.h>

int findPeakElement(const int *arr, size_t n, size_t *peakIndex)
{
    size_t low;
    size_t high;

    if ((arr == NULL) || (n == 0U) || (peakIndex == NULL)) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high) {
        const size_t mid = low + ((high - low) / 2U);
        if (arr[mid] < arr[mid + 1U]) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    *peakIndex = low;
    return 0;
}

int main(void)
{
    int arr[] = { 1, 3, 20, 4, 1, 0 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t peakIndex = 0U;
    int result;

    result = findPeakElement(arr, n, &peakIndex);
    if (result != 0) {
        (void)fprintf(stderr, "Error: invalid input to findPeakElement\n");
        return EXIT_FAILURE;
    }

    if (printf("Peak element is %d at index %zu\n", arr[peakIndex], peakIndex) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}