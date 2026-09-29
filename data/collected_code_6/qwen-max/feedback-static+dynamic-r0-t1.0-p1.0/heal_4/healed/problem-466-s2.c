#include <stdio.h>
#include <limits.h>

int find_peak(const int *array, size_t n) {
    if (n == 0) return INT_MIN;

    int peak = array[0];
    for (size_t i = 1; i < n; ++i) {
        if (array[i] > peak) {
            peak = array[i];
        }
    }
    return peak;
}

int main() {
    const int arr[] = {1, 3, 5, 4, 6, 2, 10, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int peak = find_peak(arr, n);
    printf("Peak element is: %d\n", peak);

    const int test1[] = {1, 3, 2};
    const int test2[] = {9};
    const int test3[] = {1, 2, 3, 4, 5};

    printf("Test 1 - Peak element is: %d\n", find_peak(test1, 3));
    printf("Test 0 - Peak element is: %d\n", find_peak(test2, 1));
    printf("Test 2 - Peak element is: %d\n", find_peak(test3, 5));

    return 0;
}