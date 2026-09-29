#include <stdio.h>
#include <stdlib.h>

int findPeakElement(const int *arr, size_t n)
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
    return (int)low;
}

int main(void)
{
    int arr[] = {1, 3, 20, 4, 1, 0};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 6
     */
    size_t n = sizeof(arr) / sizeof(arr[0]);

    /* Possible weaknesses found:
     *  Condition 'n==0' is always false
     *  Condition 'n==0' is always false [knownConditionTrueFalse]
     */
    if (n == 0) {
        fprintf(stderr, "Array is empty\n");
        return EXIT_FAILURE;
    }

    int peakIndex = findPeakElement(arr, n);

    if (peakIndex < 0 || (size_t)peakIndex >= n) {
        fprintf(stderr, "Invalid peak index computed\n");
        return EXIT_FAILURE;
    }

    if (printf("Peak element is %d at index %d\n", arr[peakIndex], peakIndex) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}