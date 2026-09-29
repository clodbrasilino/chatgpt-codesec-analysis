#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  */

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
    int arr[] = {1, 3, 5, 4, 6, 2, 10, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int peak = find_peak(arr, n);
    printf("Peak element is: %d\n", peak);

    return 0;
}