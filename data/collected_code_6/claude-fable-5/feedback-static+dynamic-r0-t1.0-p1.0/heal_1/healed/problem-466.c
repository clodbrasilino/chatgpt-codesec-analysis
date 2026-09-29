#include <stdio.h>
#include <stdlib.h>

size_t findPeakElement(const int *arr, size_t n)
{
    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] < arr[mid + 1]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

int main(void)
{
    int arr[] = {1, 3, 20, 4, 1, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    size_t peakIndex = findPeakElement(arr, n);

    if (printf("Peak element is %d at index %zu\n", arr[peakIndex], peakIndex) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}