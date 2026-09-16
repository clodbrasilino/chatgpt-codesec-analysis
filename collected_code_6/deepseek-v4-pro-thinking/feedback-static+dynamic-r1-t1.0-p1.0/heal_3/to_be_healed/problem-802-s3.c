#include <stdio.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 0
  *  test case 2 failed: expected 3, got 0
  *  test case 0 failed: expected 1, got 0
  */

int countRotations(const int arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return arr[low];
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", countRotations(arr, n));

    return 0;
}