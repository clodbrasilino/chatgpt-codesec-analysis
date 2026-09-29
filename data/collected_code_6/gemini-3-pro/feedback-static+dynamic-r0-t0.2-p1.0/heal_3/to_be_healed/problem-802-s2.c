#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  */

int countRotations(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }

        if (arr[mid] >= arr[low]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}

int main(void) {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = countRotations(arr1, n1);
    if (result1 != -1) {
        printf("%d\n", result1);
    }

    int arr2[] = {7, 9, 11, 12, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = countRotations(arr2, n2);
    if (result2 != -1) {
        printf("%d\n", result2);
    }

    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = countRotations(arr3, n3);
    if (result3 != -1) {
        printf("%d\n", result3);
    }

    return 0;
}