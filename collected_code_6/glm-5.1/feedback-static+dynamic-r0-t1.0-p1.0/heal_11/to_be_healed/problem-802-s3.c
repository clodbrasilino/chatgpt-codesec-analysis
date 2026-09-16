#include <stdio.h>
#include <stdlib.h>

int find_minimum_index(const int *arr, int low, int high) {
    if (low == high) {
        return low;
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[high]) {
        return find_minimum_index(arr, low, mid);
    }
    if (arr[mid] > arr[high]) {
        return find_minimum_index(arr, mid + 1, high);
    }
    return find_minimum_index(arr, low, high - 1);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
  */

int count_rotations(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    return find_minimum_index(arr, 0, n - 1);
}

int main(void) {
    int arr1[] = {2, 2, 2, 3, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = count_rotations(arr1, n1);
    printf("%d\n", res1);

    int arr2[] = {7, 9, 11, 12, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = count_rotations(arr2, n2);
    printf("%d\n", res2);

    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = count_rotations(arr3, n3);
    printf("%d\n", res3);

    int arr4[] = {15, 18, 2, 3, 6, 12};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int res4 = count_rotations(arr4, n4);
    printf("%d\n", res4);

    int res5 = count_rotations(NULL, 5);
    printf("%d\n", res5);

    return 0;
}