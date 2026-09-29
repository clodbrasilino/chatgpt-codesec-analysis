#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

int binary_search(const int *arr, int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {-10, -3, 0, 1, 2, 11, 15, 21, 33, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 11;
    int result = binary_search(arr, n, target);
    printf("Element %s at index: %d\n", (result != -1) ? "found" : "not found", result);

    target = 7;
    result = binary_search(arr, n, target);
    printf("Element %s at index: %d\n", (result != -1) ? "found" : "not found", result);

    target = 45;
    result = binary_search(arr, n, target);
    printf("Element %s at index: %d\n", (result != -1) ? "found" : "not found", result);

    return 0;
}