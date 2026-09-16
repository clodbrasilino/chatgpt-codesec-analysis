#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 1
  *  test case 2 failed: expected 3, got 1
  */

int countRotations(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_idx]) {
            min_idx = i;
        }
    }
    return min_idx;
}

int main(void) {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", countRotations(arr1, n1));

    int arr2[] = {7, 9, 11, 12, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", countRotations(arr2, n2));

    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", countRotations(arr3, n3));

    int arr4[] = {2, 1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", countRotations(arr4, n4));

    printf("%d\n", countRotations(NULL, 5));

    return 0;
}